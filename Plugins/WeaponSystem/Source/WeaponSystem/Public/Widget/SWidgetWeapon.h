#pragma once
#include "CoreMinimal.h"
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

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
		class UTextBlock* CurrentAmmoText;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
		class UTextBlock* CurrentAmmoInBagText;

	UPROPERTY(meta = (BindWidget))
		class UImage* AimImage_01;

	UPROPERTY(meta = (BindWidget))
		class UImage* AimImage_02;

	UPROPERTY(meta = (BindWidget))
		class UImage* AimImage_03;

	UPROPERTY(meta = (BindWidget))
		class UImage* AimImage_04;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* AimSizeBox;

    UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
		class ASWeapon* aWeaponRef;

    
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void SetupWidget(class ASWeapon* weaponref);

    UFUNCTION(BlueprintNativeEvent)
    void AmmoStateChanged(int32 iCurrentAmmo,int32 iCurrentAmmoInBag);
};
