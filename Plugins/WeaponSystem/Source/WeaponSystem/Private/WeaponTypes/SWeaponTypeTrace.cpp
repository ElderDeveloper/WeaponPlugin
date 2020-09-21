#include "WeaponTypes/SWeaponTypeTrace.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

void ASWeaponTypeTrace::F_ProcessFire()
{
    Super::F_ProcessFire();

    FVector StartLocation;
    
    FVector EndLocation;
    
    FRotator SpawnRotation;
    
    F_CalculateSpread(StartLocation,EndLocation,SpawnRotation);
    
    FCollisionResponseParams ResponseParams;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner());
    QueryParams.AddIgnoredActor(this);
    QueryParams.bReturnPhysicalMaterial=true;
    
    TArray<FHitResult> OutHits;

    if(GetWorld()->LineTraceMultiByChannel(OutHits,StartLocation,EndLocation,tcTraceChannel,QueryParams,ResponseParams))
    {
        fCurrentDamageOutput=FMath::RandRange(fMinDamage,fMaxDamage);
        
        if(bPointDamage)
        {
            for (FHitResult i : OutHits)
            {

               UGameplayStatics::ApplyPointDamage(i.GetActor(),fCurrentDamageOutput,StartLocation,i,GetOwner()->GetInstigatorController(),this,dtDamageType);
                F_ProcessImpactEffects(i);
               if (fDamageReductionOnImpact==0)
               {
                   fCurrentDamageOutput=0;
                   break;
               }
                fCurrentDamageOutput-=fDamageReductionOnImpact;
               if (fCurrentDamageOutput<=0)
               {
                   break;
               }
            }
  
        }
        else
        {
            for (FHitResult i : OutHits)
            {
                UGameplayStatics::ApplyDamage(i.GetActor(),fCurrentDamageOutput,GetOwner()->GetInstigatorController(),this,dtDamageType);
                if (fDamageReductionOnImpact==0)
                {
                    fCurrentDamageOutput=0;
                    break;
                }
                fCurrentDamageOutput-=fDamageReductionOnImpact;
                if (fCurrentDamageOutput<=0)
                {
                    break;
                }
            }
        }
    
    }
    
    if (bShouldDrawLine)
    {
        DrawDebugLine(GetWorld(),StartLocation,EndLocation,cDebugeColor,false,fLineDuration,0,fLineTickness);
    }
}

void ASWeaponTypeTrace::F_ProcessImpactEffects(FHitResult i)
{
    
    if (i.GetComponent()->IsSimulatingPhysics())
    {
        i.GetComponent()->AddImpulse(i.ImpactNormal*fImpactForce*-1,i.BoneName);
    }
    
    if (i.PhysMaterial.IsValid())
    {
        if (EffectsTable)
        {
            for (FName row : EffectsTable->GetRowNames())
            {
                FImpactStruct * localImpact= EffectsTable->FindRow<FImpactStruct>(row,"");
                
                if (i.PhysMaterial.Get()==localImpact->phPhysicsMaterial)
                {
                  if (structHitEffects.pImpactParticle)
                  UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),localImpact->pImpactParticle,i.ImpactPoint,i.ImpactPoint.Rotation(),localImpact->ParticleScale);

                  if (structHitEffects.sImpactSound)
                  UGameplayStatics::SpawnSoundAtLocation(this,localImpact->sImpactSound,i.ImpactPoint);

                  if (structHitEffects.mImpactDecal)
                  UGameplayStatics::SpawnDecalAtLocation(this,localImpact->mImpactDecal,localImpact->DecalScale,i.ImpactPoint,i.ImpactPoint.Rotation()+FRotator(-90,0,0),localImpact->fDecalLifeSpan);

                    return;
                }
            }
            F_StructImpactEffects(i); 
        }
        
        else
        {      F_StructImpactEffects(i);     }
        
    }
    else
     {     F_StructImpactEffects(i);     }



}


void ASWeaponTypeTrace::F_StructImpactEffects(FHitResult i)
{
    if (structHitEffects.pImpactParticle)
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),structHitEffects.pImpactParticle,i.ImpactPoint,i.ImpactPoint.Rotation(),structHitEffects.ParticleScale);

    if (structHitEffects.sImpactSound)
        UGameplayStatics::SpawnSoundAtLocation(this,structHitEffects.sImpactSound,i.ImpactPoint);

    if (structHitEffects.mImpactDecal)
        UGameplayStatics::SpawnDecalAtLocation(this,structHitEffects.mImpactDecal,structHitEffects.DecalScale,i.ImpactPoint,i.ImpactPoint.Rotation()+FRotator(-90,0,0),structHitEffects.fDecalLifeSpan);

}
