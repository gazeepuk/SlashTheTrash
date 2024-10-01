// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Damage_ExecCalc.generated.h"

/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API UDamage_ExecCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UDamage_ExecCalc();

	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
