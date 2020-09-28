// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SData.h"
#include "Components/TimelineComponent.h"
#include "SWeapon.generated.h"

#define SpawnParticleAttachedValidate(Emitter,component,socket) if(Emitter){UGameplayStatics::SpawnEmitterAttached(Emitter,component,socket); }
#define SpawnAudioAttachedValidate(Sound,component,socket) if(Sound){UGameplayStatics::SpawnSoundAttached(Sound,component,socket); }

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAmmoStateChanged,int32,iCurrentAmmo,int32,iCurrentAmmoInBag);

class USoundBase;
class UParticleSystem;
class UAnimSequence;
class USkeletalMeshComponent;

UCLASS()
class ASWeapon : public AActor
{
	GENERATED_BODY()

public:
	
	ASWeapon();

	FAmmoStateChanged AmmoStateChangedDelegate;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite )
	USkeletalMeshComponent*WeaponSkeleton;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite)
	USkeletalMeshComponent*SightComponent;
	
	UPROPERTY(EditDefaultsOnly)
	FName SightAttachmentName;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite)
	USkeletalMeshComponent*SilencerComponent;
	
	UPROPERTY(EditDefaultsOnly)
	FName SilencerAttachmentName;

	


//<<<<<<<<<<<<<<<<<<<<<<<<<<<< PROPERTIES >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	/** Weapons Relative location after spawned and attached to player skeletal mesh */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon")
	FTransform tWeaponRelativeTransform;

	/** Store witch socket player choose */
	FName nWeaponAttachSocketName;
	
	//<<<<<<<<<<<<<<<<<<<<<FIRE TYPE>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	/** This can change how weapon behaves and can be changed during gameplay */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Fire")
	TEnumAsByte<E_WeaponFireType> eWeaponFireType;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Fire")
	TEnumAsByte<ECollisionChannel> FireCalculateChannel;

	/** Number of bullets each shot contains */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Fire")
	int32 iNumberOfBulletsFired=1;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Fire")
	float fTimeBetweenFire=0.12;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Fire")
	FName nFireSocketName="Muzzle";

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Fire|Burst")
	float fTimeBetweenBurst=0.6;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Fire|Burst")
	int32 iNumberOfBurst=3;


	
	//<<<<<<<<<<<<<<<<<<<<< AMMO >>>>>>>>>>>>>>>>>>>>>>>>>

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Ammo")
	int32 iCurrentAmmo=24;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Ammo")
	int32 iCurrentAmmoInBag=120;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Ammo")
	bool bHasUnlimitedAmmo=false;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Ammo")
	bool bHasUnlimitedBackPackAmmo=false;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Ammo")
	int32 iMaxAmmoInClip=24;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Ammo")
	int32 iMaxAmmoInBag=240;

	

	//<<<<<<<<<<<<<<<<<<<<<<<<<<< RELOAD >>>>>>>>>>>>>>>>>>>>
	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Reload")
	bool bShouldAutoReload=false;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Reload")
	UAnimSequence *animWeaponReloadAnimation;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Reload")
	USoundBase* soundWeaponReloadSound;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Reload")
	float fAnimMinusToReloadTime=0;

	
	
	//<<<<<<<<<<<<<<<<<<<<<<<< SPREAD >>>>>>>>>>>>>>>>>>>>>>>>>>>

	/**  */
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="Weapon|Spread|Passive")
	float fCurrentSpread=0;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Spread")
	bool bShouldSpread=false;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Spread")
	bool bShouldStopAtMaxSpread=false;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Spread")
	float fBeginSpread=0;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Spread")
	float fSpreadRiseCount=0.2;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Spread")
	float fSpreadDecreaseCount=0.02;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Spread")
	float fMaxSpread=5;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Spread")
	float fSpreadDecreaseDelay=0.3;



	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< RECOIL >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Recoil")
	bool bUseRecoil=false;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Recoil")
	UCurveFloat* uRecoilCurve;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Recoil")
	float fMaxRecoil=0;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Recoil")
	bool bRecoilReturn=true;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Recoil")
	float fRecoilReturnSpeed=0.2;

	/**  */
	UPROPERTY(BlueprintReadOnly,Category="Weapon|Recoil")
	float fProcessedRecoil=0;

	/**  */
	FTimeline tlRecoilTimeline;

	
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< CAMERA SHAKE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|CameraShake")
	TSubclassOf<class UCameraShake> oWeaponMuzzleCameraShake;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|CameraShake")
	float fCameraShakeInnerRadius=100;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|CameraShake")
	float fCameraShakeOuterRadius=100;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|CameraShake")
	float fCameraShakeFalloff=0;



	
	// <<<<<<<<<<<<<<<<<<<<<<< EFFECTS >>>>>>>>>>>>>>>>>>>>>>>>>>
	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Effects")
	bool bUsingNotifyForFire=false;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Effects")
	UAnimSequence *animWeaponFireAnimation;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Effects")
	UParticleSystem* pWeaponMuzzle;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Effects")
	FTransform tWeaponMuzzleTransform=FTransform(FRotator().ZeroRotator.Quaternion(),FVector(0,0,0),FVector(1.f,1.f,1.f));

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Effects")
	USoundBase* sFireStartSound;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Effects")
	USoundBase* sFireLoopSound;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Effects")
	USoundBase* sFireEndSound;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Effects")
	USoundBase* sClipEmptySound;


	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Aim >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Aim")
	UCurveFloat* uAimCurveFloat;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Aim")
	FName nWeaponAimSocketName="AimSocket";

	/**  */
	FTimeline tlAimTimeline;

	/**  */
	bool bIsAiming=false;

	/**  */
	FVector PlayerCameraRelative;
	
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PLAYER ANIMATIONS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|PlayerAnimations")
	UAnimMontage *animPlayerFireMontage;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|PlayerAnimations")
	UAnimMontage* animPlayerAimFireMontage;

	/**  */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|PlayerAnimations")
	UAnimMontage*animPlayerReloadMontage;




	
private:

// <<<<<<<<<<<<<<<<<<<<<<<< PRIVATE PROPERTIES >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	FTimerHandle AutoFireHandle;
	FTimerHandle SingleFireHandle;
	FTimerHandle BurstFireHandle;
	FTimerHandle ReloadHandle;
	FTimerHandle SpreadReturnHandle;
	FTimerHandle SpreadDecreasingHandle;
	FTimerHandle RecoilHandle;

	/**  */
	class UAudioComponent* audioFireLoop;

	/**  */
	FAttachmentTransformRules *AttachmentTransformRules;

	/**  */
	FOnMontageBlendingOutStarted ReloadMontageBlendOut;

	/**  */
	USkeletalMeshComponent* PlayerSkeletonComponent;

	/**  */
	bool bLoopSoundValid;
	bool bCanFireWeapon=true;
	bool bHasAmmoInClip=true;
	bool bIsReloading=false;
	bool bFired=false;

	/**  */
	int32 BurstIndex=1;

	/**  */
	APlayerController* OwnerAsPlayerController;
	/**  */
	APlayerCameraManager*OwnerCameraNanager;
	/**  */
	ACharacter* OwnerAsCharacter;
	/**  */
	class UCameraComponent*OwnerCamera;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< FUNCTIONS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
protected:

	

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	/**  */
	void F_CalculateSpread(FVector& StartLocation , FVector& EndLocation , FRotator& SpawnRotation ,const float Distance=10000000);
	
public:

	/**  */
	virtual void F_ProcessFire();

	/**  */
	void F_FireEvents();

	/**  */
	void F_RiseSpread();

	//<<<<<<<<<<<<<<<<<<<<<<  Controllers >>>>>>>>>>>>>>>>>>>

	/**  */
	void F_RemoveAmmo(int32 RemoveAmount = 1);

	//<<<<<<<<<<<<<<<<< Effects >>>>>>>>>>>>>>>>>>

	/**  */
	void F_PlaySingleFireEffects();

	//<<<<<<<<<<<<<<<<< Aim >>>>>>>>>>>>>>>>>>>
	/**  */
	void F_ProcessAim(const bool bStart);
	

	/**  */
	UFUNCTION()
	void F_ProcessRecoil();

	/**  */
	UFUNCTION()
    void F_StartRecoilBack();

	/**  */
	UFUNCTION()
    void F_ProcessRecoilTimeline();

	/**  */
	UFUNCTION()
    void F_ProcessAimTimeline();


	/**  */
	UFUNCTION(BlueprintCallable)
	void F_RequestBeginFire();

	/**  */
	UFUNCTION(BlueprintCallable)
	void F_RequestEndFire();

	/**  */
	UFUNCTION(BlueprintCallable)
	void F_RequestReload();

	/**  */
	UFUNCTION(BlueprintCallable)
	void F_SetupWeapon( APawn* NewOwner , USkeletalMeshComponent*PlayerSkeletalMesh);
	

	

private:



	//<<<<<<<<<<<<<<<<< Effects >>>>>>>>>>>>>>>>>>
	/**  */
	void F_ReloadBlendOut(UAnimMontage* animMontage, bool bInterrupted);

	/**  */
	void F_ReloadBlendOut();

	/**  */
	void F_FireAudioLoop(class UAudioComponent* audio);

	//<<<<<<<<<<<<<<<<<<<<<<< EVENTS >>>>>>>>>>>>>>>>>>>>>>>>
	/**  */
	void F_PlayAutoFire();

	/**  */
	void F_PlayerBurstFire();

	/**  */
	void F_DecreaseSpreadStarter();

	/**  */
	void F_DecreaseSpread();

	//<<<<<<<<<<<<<<<<< RECOIL >>>>>>>>>>>>>>>>>>
	/**  */
    void F_RecoilBack();


	//<<<<<<<<<<<<<<<<<<<<<<<< Aim >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	/**  */
	UAnimMontage* F_RetrunPlayerFireMontage();


	//<<<<<<<<<<<<<<<<<<<<<< is valid Returners >>>>>>>>>>>>>>>>>>>
	/**  */
	void F_SetNotFired();



	
};

