// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttackAnimNotify.generated.h"

/**
 * 
 */


UCLASS()
class SLASHTHETRASH_API UAttackAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AttackEventTag;
	
};
