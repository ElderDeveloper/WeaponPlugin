#pragma once
#include "SWeapon.h"
#include "SWeaponTypeProjectile.generated.h"

UCLASS()
class ASWeaponTypeProjectile : public ASWeapon
{
    GENERATED_BODY()

 
    
public:
    ASWeaponTypeProjectile();

    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Bullet")
    bool bIsReplicatedBullet;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Bullet")
    TSubclassOf<AActor> aProjectileClass;

    FActorSpawnParameters actorSpawnParameters = FActorSpawnParameters();

private:
    virtual void F_ProcessFire() override;

};
