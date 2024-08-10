// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/STTGameplayAbilityBase.h"
#include "JumpAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API UJumpAbilityBase : public USTTGameplayAbilityBase
{
	GENERATED_BODY()

public:

	UJumpAbilityBase();

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	TSubclassOf<UGameplayEffect> JumpEffectClass;
};
