#pragma once
#include "Blueprint/UserWidget.h"
#include "SWidgetWeapon.generated.h"


UCLASS(BlueprintType,Blueprintable)
class USWidgetWeapon : public UUserWidget
{
    GENERATED_BODY()
public:

    
    UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
    float fCurrentSpread;

    UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
    int32 iAmmoInClip;

    UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
    int32 iAmmoInBag;

    UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
    class ASWeapon* aWeaponRef;
    
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void SetupWidget(class ASWeapon* weaponref);

    UFUNCTION(BlueprintImplementableEvent)
    void AmmoStateChanged(int32 iCurrentAmmo,int32 iCurrentAmmoInBag);
};
