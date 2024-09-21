// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/UltimateSkillAbilities/STTUltimateSkillAbilityBase.h"
#include "UI/WidgetControllers/WidgetControllerBase.h"
#include "STTCharacterWidgetController.generated.h"

class USTTSkillAbilityBase;
class USTTAttackAbilityBase;
class ASTTCharacterBase;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SLASHTHETRASH_API USTTCharacterWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ASTTCharacterBase* GetSTTCharacter() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<USTTUltimateSkillAbilityBase> GetUltiamteAbilityClass();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<USTTSkillAbilityBase> GetSkillAbilityClass();

	UFUNCTION(BlueprintCallable,BlueprintType)
	FAbilityUIInfo GetAbilityUIInfoByClass(TSubclassOf<USTTAttackAbilityBase> AttackAbilityClass);
};
