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
        
       GetWorld()->SpawnActor<AActor>(aProjectileClass,StartLocation,SpawnRotation,actorSpawnParameters);
       GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, "aa");
    }
};

