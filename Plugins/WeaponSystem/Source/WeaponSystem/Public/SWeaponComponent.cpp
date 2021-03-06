﻿#include "SWeaponComponent.h"
#include "SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponTypes/SWeaponTypeTrace.h"
USWeaponComponent::USWeaponComponent()
{
}

void USWeaponComponent::SpawnWeapon(TSubclassOf<ASWeapon> SpawnWeaponClass, USkeletalMeshComponent* AttachComponent, const FName AttachSocket)
{
    if (SpawnWeaponClass)
    {
        if (CurrentSpawnedWeapon)
        {
            CurrentSpawnedWeapon->Destroy();
        }
        CurrentSpawnedWeapon= GetWorld()->SpawnActor<ASWeapon>(SpawnWeaponClass);
        CurrentSpawnedWeapon->AttachToComponent(AttachComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget,false),AttachSocket);
        CurrentSpawnedWeapon->F_SetupWeapon(Cast<APawn>(GetOwner()),AttachComponent);
        CurrentSpawnedWeapon->SetActorRelativeTransform(CurrentSpawnedWeapon->tWeaponRelativeTransform);
        CurrentSpawnedWeapon->nWeaponAttachSocketName=AttachSocket;
    }
}

void USWeaponComponent::BeginFire()
{
    if (CurrentSpawnedWeapon)
    {
        CurrentSpawnedWeapon->F_RequestBeginFire();
    }
}

void USWeaponComponent::EndFire()
{
    if (CurrentSpawnedWeapon)
    {
        CurrentSpawnedWeapon->F_RequestEndFire();
    }
}

void USWeaponComponent::Reload()
{
    if (CurrentSpawnedWeapon)
    {
        CurrentSpawnedWeapon->F_RequestReload();
    }
}

void USWeaponComponent::ProcessAim(const bool bStart)
{
    if (CurrentSpawnedWeapon)
    {
       bIsAiming=bStart;
       CurrentSpawnedWeapon->F_ProcessAim(bStart);
    }

}

bool USWeaponComponent::ReturnAiming()
{
    return bIsAiming;
}
