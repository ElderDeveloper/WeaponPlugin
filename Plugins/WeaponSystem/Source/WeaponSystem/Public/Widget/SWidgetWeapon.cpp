#include "SWidgetWeapon.h"

#include "SWeapon.h"



void USWidgetWeapon::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
   if (aWeaponRef)
   {
      fCurrentSpread=aWeaponRef->fCurrentSpread;
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
