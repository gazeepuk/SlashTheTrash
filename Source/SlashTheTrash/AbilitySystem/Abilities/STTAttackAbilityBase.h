// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/STTGameplayAbilityBase.h"
#include "STTAttackAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API USTTAttackAbilityBase : public USTTGameplayAbilityBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bRestoreEnergy = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bRestoreEnergy"))
	float EnergyRegenAmount = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bRestoreEnergy"))
	TSubclassOf<UGameplayEffect> RestoreBattleEnergyEffectClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bRestoreEnergy"))
	FGameplayTag BattleEnergyRegenTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> AttackEffectClass;
	
	UFUNCTION(BlueprintCallable)
	virtual void PerformAbilityAction();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UFUNCTION(BlueprintCallable)
	virtual void RestoreEnergy();

	UFUNCTION(BlueprintCallable)
	virtual void RestoreEnergyOnce();
	void ResetRestoreEnergyOnce();

private:
	bool bCanRestoreEnergyOnce = false;
};
