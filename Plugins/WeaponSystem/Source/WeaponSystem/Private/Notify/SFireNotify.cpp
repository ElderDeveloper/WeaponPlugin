#include "WeaponSystem/Public/Notify/SFireNotify.h"
#include "WeaponSystem/Public/SWeapon.h"


void USFireNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    ASWeapon* LocalWeapon = Cast<ASWeapon>(MeshComp->GetOwner());
    if(LocalWeapon)
    {
        if (LocalWeapon->bUsingNotifyForFire)
        {
            LocalWeapon->F_FireEvents();
        }

    }
}
