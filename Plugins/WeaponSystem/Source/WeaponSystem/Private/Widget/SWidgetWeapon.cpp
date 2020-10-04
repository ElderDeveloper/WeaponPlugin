#include "WeaponSystem/Public/Widget/SWidgetWeapon.h"
#include "Components/TextBlock.h"
#include "SWeapon.h"
#include "Components/SizeBox.h"


void USWidgetWeapon::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
   if (aWeaponRef)
   {
      if (aWeaponRef->bIsAiming)  AimSizeBox->SetVisibility(ESlateVisibility::Hidden);

      else AimSizeBox->SetVisibility(ESlateVisibility::HitTestInvisible);

      AimSizeBox->SetWidthOverride(50 + (aWeaponRef->fCurrentSpread * 100));
      AimSizeBox->SetHeightOverride(50 + (aWeaponRef->fCurrentSpread * 100));

   }
}

void USWidgetWeapon::SetupWidget(ASWeapon* weaponref)
{
   aWeaponRef=weaponref;
   if (aWeaponRef)
   {
      aWeaponRef->AmmoStateChangedDelegate.AddDynamic(this,&USWidgetWeapon::AmmoStateChanged);
      AmmoStateChanged(aWeaponRef->iCurrentAmmo,aWeaponRef->iCurrentAmmoInBag);
   }
}

void USWidgetWeapon::AmmoStateChanged_Implementation(int32 iCurrentAmmo, int32 iCurrentAmmoInBag)
{
   if (aWeaponRef)
   {
      CurrentAmmoText->SetText(FText::AsNumber(aWeaponRef->iCurrentAmmo));

      CurrentAmmoInBagText->SetText(FText::AsNumber(aWeaponRef->iCurrentAmmoInBag));
   }
}

