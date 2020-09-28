#pragma once
#include "SWeapon.h"
#include "SWeaponTypeProjectile.generated.h"

UCLASS()
class ASWeaponTypeProjectile : public ASWeapon
{
    GENERATED_BODY()

 
    
public:
    ASWeaponTypeProjectile();

    /** This is simple control for replication , spawn process is different between replicated actor and non replicated actor */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponProjectileType|Bullet")
    bool bIsReplicatedBullet;
    
    /** Any class can be selected but main intent is a class with projectile component attached */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponProjectileType|Bullet")
    TSubclassOf<AActor> aProjectileClass;


    FActorSpawnParameters actorSpawnParameters = FActorSpawnParameters();

private:
    virtual void F_ProcessFire() override;

};
