#include "WeaponTypes/SWeaponTypeProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"


ASWeaponTypeProjectile::ASWeaponTypeProjectile()
{

}

void ASWeaponTypeProjectile::F_ProcessFire()
{
    Super::F_ProcessFire();
    if (aProjectileClass)
    {
       FVector StartLocation;
       FVector EndLocation;
       FRotator SpawnRotation;
       F_CalculateSpread(StartLocation,EndLocation,SpawnRotation);
       actorSpawnParameters.Owner=GetOwner();
        
       for (int i =1 ; i<=iNumberOfBulletsFired ; i++)
       GetWorld()->SpawnActor<AActor>(aProjectileClass,StartLocation,SpawnRotation,actorSpawnParameters);

    }
};

