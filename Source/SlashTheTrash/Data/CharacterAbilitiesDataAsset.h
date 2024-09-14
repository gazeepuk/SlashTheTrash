// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterAbilitiesDataAsset.generated.h"

class USTTUltimateSkillAbilityBase;
class USTTSkillAbilityBase;
class USTTComboAttackBase;
class UGameplayAbility;
class USTTGameplayAbilityBase;
/**
 * 
 */

UCLASS()
class SLASHTHETRASH_API UCharacterAbilitiesDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	//Get all default abilities 
	TArray<TSubclassOf<UGameplayAbility>> GetDefaultAbilities() const;
	//Skill ability's getter
	TSubclassOf<USTTSkillAbilityBase> GetSkillAbilityClass() const { return DefaultSkillAbility; }
	//Ultimate ability's getter
	TSubclassOf<USTTUltimateSkillAbilityBase> GetUltimateSkillAbilityClass() const { return DefaultUltimateSkillAbility; }
private:
	//Combat attacks
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<USTTComboAttackBase>> DefaultNormalAttackAbilities;
	//Movement
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> DefaultMovementAbilities;
	//Skill ability
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USTTSkillAbilityBase> DefaultSkillAbility;
	//Ultimate skill ability
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USTTUltimateSkillAbilityBase> DefaultUltimateSkillAbility;
};
