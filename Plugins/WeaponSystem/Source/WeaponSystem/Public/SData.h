#pragma once


#include "Engine/DataTable.h"
#include "SData.generated.h"

UENUM(BlueprintType)
enum E_WeaponFireType
{
    SingleFire    UMETA(DisplayName="SingleFire"),
    AutoFire      UMETA(DisplayName="AutoFire"),
    BurstFire     UMETA(DisplayName="BurstFire")
};


USTRUCT(BlueprintType)
struct FImpactStruct : public FTableRowBase
{
    
    GENERATED_BODY()

public:
        
    UPROPERTY(EditAnywhere,BlueprintReadOnly)
    UPhysicalMaterial* phPhysicsMaterial;
    
    UPROPERTY(EditAnywhere,BlueprintReadOnly)
    class UParticleSystem *pImpactParticle;

    UPROPERTY(EditAnywhere,BlueprintReadOnly)
    FVector ParticleScale=FVector(1,1,1);
    
    UPROPERTY(EditAnywhere,BlueprintReadOnly)
    class USoundBase* sImpactSound;
    
    UPROPERTY(EditAnywhere,BlueprintReadOnly)
    class UMaterialInterface* mImpactDecal;

    UPROPERTY(EditAnywhere,BlueprintReadOnly)
    FVector DecalScale=FVector(10,10,10);

    UPROPERTY(EditAnywhere,BlueprintReadOnly)
    float fDecalLifeSpan=1;

    FImpactStruct(){};
    
};





UCLASS()
class USData : public UObject
{
    GENERATED_BODY()
public:
    
};
