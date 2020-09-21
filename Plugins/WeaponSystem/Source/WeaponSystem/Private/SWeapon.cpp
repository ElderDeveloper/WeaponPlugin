// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"
#include "Net/UnrealNetwork.h"
#include "Math/Vector.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"


// <<<<<<<<<<<<<<<<<< DEFAULT EVENTS >>>>>>>>>>>>>>

ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
    AActor::SetReplicateMovement(true);

	WeaponSkeleton=CreateDefaultSubobject<USkeletalMeshComponent>("WeaponSkeleton");
	RootComponent=WeaponSkeleton;
	
	SightComponent=CreateDefaultSubobject<USkeletalMeshComponent>("SightComponent");
	SightComponent->SetupAttachment(WeaponSkeleton);
	
	SilencerComponent=CreateDefaultSubobject<USkeletalMeshComponent>("SilencerComponent");
	SilencerComponent->SetupAttachment(WeaponSkeleton);

	AttachmentTransformRules= new FAttachmentTransformRules(EAttachmentRule::KeepRelative,true);

	ReloadMontageBlendOut.BindUObject(this,&ASWeapon::F_ReloadBlendOut);

	WeaponCameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("WeaponCameraComponent"));
	WeaponCameraComponent->SetupAttachment(RootComponent);
	WeaponCameraComponent->SetActive(false);
}


void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	bLoopSoundValid=sFireLoopSound!=nullptr;
	if(bShouldSpread)fCurrentSpread=fBeginSpread;

	if (uRecoilCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("F_ProcessRecoilTimeline"));
		TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("F_StartRecoilBack") });
		tlRecoilTimeline.AddInterpFloat(uRecoilCurve, TimelineCallback);
		tlRecoilTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
	
}


void ASWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	tlRecoilTimeline.TickTimeline(DeltaSeconds);
}



void ASWeapon::OnConstruction(const FTransform& Transform)
{

	SightComponent->AttachToComponent(WeaponSkeleton, *AttachmentTransformRules,SightAttachmentName);
	
	SilencerComponent->AttachToComponent(WeaponSkeleton, *AttachmentTransformRules,SilencerAttachmentName);

	WeaponCameraComponent->SetRelativeTransform(CameraRelativeTransform);
}



void ASWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const{}




//<<<<<<<<<<<<<<<<<< FIRE >>>>>>>>>>>>>>>>>>>>

void ASWeapon::F_RequestBeginFire()
{
	if (!bHasAmmoInClip)
	{
		SpawnAudioAttachedValidate(sClipEmptySound,WeaponSkeleton,nFireSocketName);
		return;
	}
	if (!bFired && !bIsReloading && bCanFireWeapon && bHasAmmoInClip)
	{
		bFired=true;
		
		if(!bUsingNotifyForFire)
		F_FireEvents();
		
		fProcessedRecoil=0;
		
		if (animWeaponFireAnimation)	WeaponSkeleton->PlayAnimation(animWeaponFireAnimation,false);
		
		if(PlayerSkeletonComponent && animPlayerFireMontage)	{	PlayerSkeletonComponent->GetAnimInstance()->Montage_Play(animPlayerFireMontage);	}
		
		switch (eWeaponFireType)
		{
			case SingleFire:
				GetWorld()->GetTimerManager().SetTimer(SingleFireHandle,this,&ASWeapon::F_SetNotFired,fTimeBetweenFire,false);
				break;

			
			case AutoFire:
				if (bLoopSoundValid)
				{
					audioFireLoop=UGameplayStatics::SpawnSoundAttached(sFireLoopSound,WeaponSkeleton,nFireSocketName);
					if (audioFireLoop)
					{
						audioFireLoop->bAutoDestroy=false;
						audioFireLoop->OnAudioFinishedNative.AddUObject(this,&ASWeapon::F_FireAudioLoop);
					}
				}
				GetWorld()->GetTimerManager().SetTimer(AutoFireHandle ,this ,&ASWeapon::F_PlayAutoFire,fTimeBetweenFire,true);
				break;

			
			case BurstFire:
				GetWorld()->GetTimerManager().SetTimer(BurstFireHandle,this,&ASWeapon::F_PlayerBurstFire , fTimeBetweenBurst,true);
				break;

			
			default:
				break;
		}
	}


}



void ASWeapon::F_ProcessFire(){}



void ASWeapon::F_RequestEndFire()
{
	if (eWeaponFireType==AutoFire)
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoFireHandle);
		bFired=false;
	}
	SpawnAudioAttachedValidate(sFireEndSound,WeaponSkeleton,nFireSocketName);
}



void ASWeapon::F_PlayAutoFire()
{
	if(!bUsingNotifyForFire) F_FireEvents();
	
	if (animWeaponFireAnimation)	WeaponSkeleton->PlayAnimation(animWeaponFireAnimation,false);
	
	if(PlayerSkeletonComponent && animPlayerFireMontage)	{	PlayerSkeletonComponent->GetAnimInstance()->Montage_Play(animPlayerFireMontage);	}
	
}



void ASWeapon::F_PlayerBurstFire()
{
	if(!bUsingNotifyForFire) F_FireEvents();

	if (animWeaponFireAnimation)	WeaponSkeleton->PlayAnimation(animWeaponFireAnimation,false);
	
	if(PlayerSkeletonComponent && animPlayerFireMontage)	{	PlayerSkeletonComponent->GetAnimInstance()->Montage_Play(animPlayerFireMontage);	}
	
	BurstIndex++;
	
	if(BurstIndex>=iNumberOfBurst)
	{
		BurstIndex=1;
		GetWorld()->GetTimerManager().SetTimer(SingleFireHandle,this,&ASWeapon::F_SetNotFired,fTimeBetweenFire,false);
		GetWorld()->GetTimerManager().ClearTimer(BurstFireHandle);
	}
	
}



void ASWeapon::F_FireEvents()
{
	for (int32 i =1 ; i<=iNumberOfBulletsFired;i++)
	{
		F_ProcessFire();
	}
	
	F_RemoveAmmo();
	F_PlaySingleFireEffects();
	F_RiseSpread();
	F_ProcessRecoil();
}



// <<<<<<<<<<<<<<<<<<<<< EFFECTS >>>>>>>>>>>>>>>>>

void ASWeapon::F_PlaySingleFireEffects()
{
	if (oWeaponMuzzleCameraShake && OwnerAsPlayerController)	OwnerAsPlayerController->PlayerCameraManager->PlayCameraShake(oWeaponMuzzleCameraShake);
	
	if (pWeaponMuzzle) UGameplayStatics::SpawnEmitterAttached(pWeaponMuzzle,WeaponSkeleton,nFireSocketName,FVector(ForceInit),tWeaponMuzzleTransform.Rotator(),tWeaponMuzzleTransform.GetScale3D());
	
	if (!bLoopSoundValid && sFireStartSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(),sFireStartSound,WeaponSkeleton->GetSocketLocation(nFireSocketName));
}



void ASWeapon::F_FireAudioLoop(class UAudioComponent* audio)
{
	if (bFired)
	{
		audioFireLoop->Play(0);
	}

}




//<<<<<<<<<<<<<<<<<<<<< RELOAD >>>>>>>>>>>>>>>>>>>>>>

void ASWeapon::F_RequestReload()
{
	if (!bIsReloading && iCurrentAmmoInBag>0)
	{
	bIsReloading=true;
	SpawnAudioAttachedValidate(soundWeaponReloadSound,WeaponSkeleton,nFireSocketName);
		
	if(PlayerSkeletonComponent && animPlayerReloadMontage)	{	PlayerSkeletonComponent->GetAnimInstance()->Montage_Play(animPlayerReloadMontage);	}
		
	if (animWeaponReloadAnimation)
	{
		WeaponSkeleton->PlayAnimation(animWeaponReloadAnimation,false);
		GetWorld()->GetTimerManager().SetTimer(ReloadHandle,this,&ASWeapon::F_ReloadBlendOut,animWeaponReloadAnimation->GetPlayLength()-fAnimMinusToReloadTime,false);
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadHandle,this,&ASWeapon::F_ReloadBlendOut,fAnimMinusToReloadTime,false);	
	bIsReloading=false;
	}

}



void ASWeapon::F_ReloadBlendOut(UAnimMontage* animMontage, bool bInterrupted)
{
	const int32 Request=iMaxAmmoInClip-iCurrentAmmo;

	if (iCurrentAmmoInBag>=Request)
	{
		iCurrentAmmo=iMaxAmmoInClip;
		iCurrentAmmoInBag-=Request;
	}
	else if(iCurrentAmmo < Request)
	{
		iCurrentAmmo=Request-iCurrentAmmoInBag;
		iCurrentAmmoInBag=0;
	}
	bIsReloading=false;
	AmmoStateChangedDelegate.Broadcast(iCurrentAmmo,iCurrentAmmoInBag);
}


void ASWeapon::F_ReloadBlendOut()
{
	const int32 Request=iMaxAmmoInClip-iCurrentAmmo;

	if (iCurrentAmmoInBag>=Request)
	{
		iCurrentAmmo=iMaxAmmoInClip;
		iCurrentAmmoInBag-=Request;
		bHasAmmoInClip=true;
	}
	else if(iCurrentAmmoInBag < Request)
	{
		iCurrentAmmo=iCurrentAmmo+iCurrentAmmoInBag;
		iCurrentAmmoInBag=0;
		bHasAmmoInClip=true;
	}
	
	bIsReloading=false;
	AmmoStateChangedDelegate.Broadcast(iCurrentAmmo,iCurrentAmmoInBag);
}




//<<<<<<<<<<<<<<<<<<<<<< EVENTS >>>>>>>>>>>>>>>>>>>>>>>

void ASWeapon::F_SetNotFired(){bFired=false;}



void ASWeapon::F_RemoveAmmo(int32 RemoveAmount)
{
	iCurrentAmmo-=RemoveAmount;
	if (iCurrentAmmo<=0)
	{
		iCurrentAmmo=0;
		
		bHasAmmoInClip=false;
		
		if(eWeaponFireType==AutoFire) GetWorld()->GetTimerManager().ClearTimer(AutoFireHandle);
		
		if (bShouldAutoReload && iCurrentAmmoInBag>0)
		{
			FTimerHandle ReloadLocalHandle;
			GetWorld()->GetTimerManager().SetTimer(ReloadLocalHandle,this,&ASWeapon::F_RequestReload,fTimeBetweenFire+0.3,false);
		}
	}
	AmmoStateChangedDelegate.Broadcast(iCurrentAmmo,iCurrentAmmoInBag);
}



void ASWeapon::F_SetupWeapon(APawn* NewOwner , USkeletalMeshComponent*PlayerSkeletalMesh)
{
	if (PlayerSkeletalMesh)	PlayerSkeletonComponent=PlayerSkeletalMesh;
	
	SetOwner(NewOwner);
	OwnerAsPlayerController=Cast<APlayerController>(GetOwner()->GetInstigatorController());
	OwnerAsCharacter=Cast<ACharacter>(NewOwner);
	if(OwnerAsPlayerController) OwnerCameraNanager=OwnerAsPlayerController->PlayerCameraManager;
	
}




//<<<<<<<<<<<<<<<<<<<<<<<<<< RECOIL >>>>>>>>>>>>>>>>>>>>>>>>>

void ASWeapon::F_ProcessRecoil()
{
	if (uRecoilCurve && bUseRecoil)
	{
		GetWorld()->GetTimerManager().ClearTimer(RecoilHandle);
		tlRecoilTimeline.PlayFromStart();
	}
}



void ASWeapon::F_ProcessRecoilTimeline()
{
	if (OwnerAsCharacter)
	{
		float CurveAmount = uRecoilCurve->GetFloatValue(tlRecoilTimeline.GetPlaybackPosition());
		CurveAmount=FMath::Abs(CurveAmount)*(-1);
		fProcessedRecoil=fProcessedRecoil+CurveAmount;
		OwnerAsCharacter->AddControllerPitchInput(CurveAmount);
	}

}



void ASWeapon::F_StartRecoilBack()
{
	GetWorld()->GetTimerManager().SetTimer(RecoilHandle,this,&ASWeapon::F_RecoilBack,0.01,true);
}



void ASWeapon::F_RecoilBack()
{
	if (bRecoilReturn)
	{
		fProcessedRecoil=FMath::Abs(fProcessedRecoil);

		if (fProcessedRecoil>=fMaxRecoil && fMaxRecoil>0)
		{
			GetWorld()->GetTimerManager().ClearTimer(RecoilHandle);
		}

		if(OwnerAsCharacter)
		{
			OwnerAsCharacter->AddControllerPitchInput(fRecoilReturnSpeed);
		}
	
		fProcessedRecoil-=fRecoilReturnSpeed;
	
		if (fProcessedRecoil<=0)
		{
			GetWorld()->GetTimerManager().ClearTimer(RecoilHandle);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(RecoilHandle);
	}

}




//<<<<<<<<<<<<<<<<<<<<<<<<<< SPREAD >>>>>>>>>>>>>>>>>>>>>>>

void ASWeapon::F_RiseSpread()
{
	if (bShouldSpread)
	{
		fCurrentSpread+=fSpreadRiseCount;
		if (bShouldStopAtMaxSpread && fCurrentSpread>=fMaxSpread)
		{
			fCurrentSpread=fMaxSpread;
		}

		if(GetWorld()->GetTimerManager().TimerExists(SpreadReturnHandle))	GetWorld()->GetTimerManager().ClearTimer(SpreadReturnHandle);
		
		if (GetWorld()->GetTimerManager().TimerExists(SpreadDecreasingHandle))	GetWorld()->GetTimerManager().ClearTimer(SpreadDecreasingHandle);
		
		GetWorld()->GetTimerManager().SetTimer(SpreadReturnHandle,this,&ASWeapon::F_DecreaseSpreadStarter,fSpreadDecreaseDelay,false);
	}
}



void ASWeapon::F_DecreaseSpreadStarter()
{
	GetWorld()->GetTimerManager().SetTimer(SpreadDecreasingHandle,this,&ASWeapon::F_DecreaseSpread,0.05,true);
}



void ASWeapon::F_DecreaseSpread()
{
	fCurrentSpread-=fSpreadDecreaseCount;
	if (fCurrentSpread<=fBeginSpread)
	{
		fCurrentSpread=fBeginSpread;
		GetWorld()->GetTimerManager().ClearTimer(SpreadDecreasingHandle);
	}
}



void ASWeapon::F_CalculateSpread(FVector& StartLocation, FVector& EndLocation, FRotator& SpawnRotation , float Distance)
{
	if (OwnerCameraNanager)
	{
		FHitResult PlayerCameraHit;
		
		FVector End=OwnerCameraNanager->GetActorForwardVector()*100000000;
		
		End +=OwnerCameraNanager->GetCameraLocation();
		
		GetWorld()->LineTraceSingleByChannel(PlayerCameraHit,OwnerCameraNanager->GetCameraLocation(),End,FireCalculateChannel);

		SpawnRotation= UKismetMathLibrary::FindLookAtRotation(WeaponSkeleton->GetSocketLocation(nFireSocketName),PlayerCameraHit.TraceEnd);

	}
	else
	{
		SpawnRotation = WeaponSkeleton->GetSocketRotation(nFireSocketName);
	}

	StartLocation = WeaponSkeleton->GetSocketLocation(nFireSocketName);
	
	SpawnRotation.Yaw=SpawnRotation.Yaw+FMath::RandRange(fCurrentSpread*-1,fCurrentSpread);
	
	SpawnRotation.Pitch=SpawnRotation.Pitch+FMath::RandRange(fCurrentSpread*-1,fCurrentSpread);

	EndLocation=StartLocation+(UKismetMathLibrary::GetForwardVector(SpawnRotation)*Distance);
}















