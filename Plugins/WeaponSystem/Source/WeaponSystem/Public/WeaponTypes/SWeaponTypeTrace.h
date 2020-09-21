#pragma once
#include "SWeapon.h"
#include "SWeaponTypeTrace.generated.h"

UCLASS()
class ASWeaponTypeTrace : public ASWeapon
{
    GENERATED_BODY()
    
public:
    
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace")
    TEnumAsByte<ECollisionChannel> tcTraceChannel;

    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace")
    float fLineTraceDistance=1000000;
    
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace|Damage")
    bool bPointDamage;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace|Damage")
    float fMinDamage=10;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace|Damage")
    float fMaxDamage=15;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace|Damage")
    float fDamageReductionOnImpact=0;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace|Damage")
    TSubclassOf<class UDamageType>  dtDamageType;


	
    //P_LineTraceImpact data table
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace|Effects")
    float fImpactForce;


    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace|Effects")
    UDataTable* EffectsTable;

    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace|Effects")
    FImpactStruct structHitEffects;

    //E_LineDebug

    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace|Debug")
    bool bShouldDrawLine;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace|Debug")
    FColor cDebugeColor;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace|Debug")
    float fLineDuration=1;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon|Trace|Debug")
    float fLineTickness=0.2;

protected:
    virtual void F_ProcessFire() override;

    void F_ProcessImpactEffects(FHitResult i);

    void F_StructImpactEffects(FHitResult i);

private:
    float fCurrentDamageOutput;

};


