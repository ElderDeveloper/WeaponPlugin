#pragma once


#include "SWeaponComponent.generated.h"


class UBlendSpace1D;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class USWeaponComponent : public UActorComponent
{
    GENERATED_BODY()
    
public:

    USWeaponComponent();


    class ASWeapon* CurrentSpawnedWeapon;


 
    
    UFUNCTION(BlueprintCallable)
    void SpawnWeapon( TSubclassOf<class ASWeapon> SpawnWeaponClass , class USkeletalMeshComponent* AttachComponent,FName AttachSocket);

    UFUNCTION(BlueprintCallable)
    void BeginFire();
    UFUNCTION(BlueprintCallable)
    void EndFire();
    UFUNCTION(BlueprintCallable)
    void Reload();

    UFUNCTION(BlueprintCallable)
    void ProcessAim(bool bStart);

    UFUNCTION(BlueprintPure)
    bool ReturnAiming();
    
private:
    UPROPERTY()
    bool bIsAiming;
};
