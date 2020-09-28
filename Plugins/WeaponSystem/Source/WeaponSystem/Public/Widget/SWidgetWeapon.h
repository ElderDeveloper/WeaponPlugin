#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SWidgetWeapon.generated.h"


UCLASS(BlueprintType,Blueprintable)
class USWidgetWeapon : public UUserWidget
{
    GENERATED_BODY()
public:

	/** Container for holding current amount of ammo in weapon clip */
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
		class UTextBlock* CurrentAmmoText;

	/** Container for holding current amount of ammo in weapon bag */
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
		class UTextBlock* CurrentAmmoInBagText;

	/** Images for Crosshair */
	UPROPERTY(meta = (BindWidget))
		class UImage* AimImage_01;

	UPROPERTY(meta = (BindWidget))
		class UImage* AimImage_02;

	UPROPERTY(meta = (BindWidget))
		class UImage* AimImage_03;

	UPROPERTY(meta = (BindWidget))
		class UImage* AimImage_04;

	/** Aim size box contains all aim images for spread */
	UPROPERTY(meta = (BindWidget))
	class USizeBox* AimSizeBox;

	/** Current weapons referance */
    UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
		class ASWeapon* aWeaponRef;

	/** Native tick acts the same as tick in actors */
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	/** Receiving necessary information for widget */
    UFUNCTION(BlueprintCallable)
    void SetupWidget(class ASWeapon* weaponref);

	/** Delegate assignment for weapon ammo state (this is used for not using tick to track ammo state ) */
    UFUNCTION(BlueprintNativeEvent)
    void AmmoStateChanged( int32 iCurrentAmmo, int32 iCurrentAmmoInBag);
};
