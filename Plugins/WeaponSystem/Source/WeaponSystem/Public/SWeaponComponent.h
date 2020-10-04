#pragma once


#include "SWeaponComponent.generated.h"


class UBlendSpace1D;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class USWeaponComponent : public UActorComponent
{
    GENERATED_BODY()
    
public:

    USWeaponComponent();


    UPROPERTY(BlueprintReadWrite)
    class ASWeapon* CurrentSpawnedWeapon;


    UFUNCTION(BlueprintCallable)
    void SpawnWeapon( TSubclassOf<class ASWeapon> SpawnWeaponClass , class USkeletalMeshComponent* AttachComponent, const FName AttachSocket);


    UFUNCTION(BlueprintCallable)
    void BeginFire();


    UFUNCTION(BlueprintCallable)
    void EndFire();


    UFUNCTION(BlueprintCallable)
    void Reload();

    UFUNCTION(BlueprintCallable)
    void ProcessAim(const bool bStart);


    UFUNCTION(BlueprintPure)
    bool ReturnAiming();
    
private:

    UPROPERTY()
    bool bIsAiming;
};
