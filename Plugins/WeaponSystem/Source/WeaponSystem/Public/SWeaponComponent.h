#pragma once


#include "SWeaponComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class USWeaponComponent : public UActorComponent
{
    GENERATED_BODY()
    
public:

    USWeaponComponent();


    class ASWeapon* CurrentSpawnedWeapon;


    UPROPERTY(BlueprintReadOnly)
    bool isAiming;
    
    UFUNCTION(BlueprintCallable)
    void SpawnWeapon( TSubclassOf<class ASWeapon> SpawnWeaponClass , class USkeletalMeshComponent* AttachComponent,FName AttachSocket);

    UFUNCTION(BlueprintCallable)
    void BeginFire();
    UFUNCTION(BlueprintCallable)
    void EndFire();
    UFUNCTION(BlueprintCallable)
    void Reload();

    UFUNCTION(BlueprintCallable)
    void BeginAim();

    UFUNCTION(BlueprintCallable)
    void EndAim();
};
