#pragma once
#include "SWeapon.h"
#include "SWeaponTypeTrace.generated.h"

UCLASS()
class ASWeaponTypeTrace : public ASWeapon
{
    GENERATED_BODY()
    
public:
    /** Impact collision channel */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType")
    TEnumAsByte<ECollisionChannel> tcTraceChannel;

    /** How far the bullet will travel */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType")
    float fLineTraceDistance=1000000;

    /** Choosing between point damage or apply damage */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType|Damage")
    bool bPointDamage;
    
    /** Minimum damage applied on impact */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType|Damage")
    float fMinDamage=10;

    /** Maximum damage applied on impact */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType|Damage")
    float fMaxDamage=15;

    /** If this value bigger than 0 trace will pierce through and lessen the applied damage until applied damage is less than zero */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType|Damage")
    float fDamageReductionOnImpact=0;

    /** Damage type class */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType|Damage")
    TSubclassOf<class UDamageType>  dtDamageType;


   
    /** How much impulse force applied on contacted component */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType|Effects")
    float fImpactForce;

    /** P_LineTraceImpact data table */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType|Effects")
    UDataTable* EffectsTable;

    /** This struct will be used if Effects table is not defined */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType|Effects")
    FImpactStruct structHitEffects;

    //E_LineDebug

    /** if true  Draw debug line */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType|Debug")
    bool bShouldDrawLine;

    /** Color for debug line */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType|Debug")
    FColor cDebugeColor;

    /** Debug line lifetime */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType|Debug")
    float fLineDuration=1;

    /** Debug line thickness */
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WeaponTraceType|Debug")
    float fLineThickness=0.2;

protected:
    virtual void F_ProcessFire() override;

    /** Retrieves physics surface and generates impact effect struct for F_StructImpactEffects */
    void F_ProcessImpactEffects(const FHitResult i);

    /** Spawn effects defined in struct */
    void F_StructImpactEffects(const FHitResult i);

private:
    /** Holding damage amount between pierces */
    float fCurrentDamageOutput;

};


