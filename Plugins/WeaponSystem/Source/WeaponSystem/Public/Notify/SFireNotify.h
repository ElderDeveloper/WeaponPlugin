#pragma once
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SFireNotify.generated.h"

UCLASS()
class USFireNotify : public UAnimNotifyState 
{
    GENERATED_BODY()
     
    public: 

    virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
    
};