// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/STTAttackAbilityBase.h"
#include "AbilitySystem/Abilities/STTGameplayAbilityBase.h"
#include "STTComboAttackBase.generated.h"

class USTTComboAttackBase;

USTRUCT(BlueprintType, Blueprintable)
struct FComboAttackStaticInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USTTComboAttackBase> NextNormalAttackClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USTTComboAttackBase> NextHardAttackClass;
};
/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API USTTComboAttackBase : public USTTAttackAbilityBase
{
	GENERATED_BODY()
public:
	USTTComboAttackBase();
	const FComboAttackStaticInfo& GetComboAttackStaticInfo() const;
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FComboAttackStaticInfo ComboAttackStaticInfo;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
