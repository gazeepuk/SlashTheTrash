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
	//Ability animation
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bRestoreEnergy = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bRestoreEnergy"))
	float EnergyRegenAmount = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bRestoreEnergy"))
	TSubclassOf<UGameplayEffect> RestoreBattleEnergyEffectClass;
	//Tag for SetByCaller
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bRestoreEnergy"))
	FGameplayTag BattleEnergyRegenTag;

	//Effect applying to a target  
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> AbilityEffectClass;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//Main logic of the ability
	UFUNCTION(BlueprintCallable)
	virtual void PerformAbilityAction();

	//Trace for targets and apply effect to them
	virtual void ApplyEffectToTracedTarget();
	virtual void ApplyEffectToSelf();
	
	//Restore Energy after applying ability effect
	UFUNCTION(BlueprintCallable)
	virtual void RestoreEnergy();
	UFUNCTION(BlueprintCallable)
	//void RestoreEnergy() but works once. Reset on EndAbility
	virtual void RestoreEnergyOnce();
	void ResetRestoreEnergyOnce();

	UPROPERTY(EditDefaultsOnly)
	bool bTargetIsSelf = false;
private:
	//Using for ResetRestoreEnergyOnce check
	bool bCanRestoreEnergyOnce = false;
};
