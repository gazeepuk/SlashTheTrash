// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CharacterAbilitiesDataAsset.h"

#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/Abilities/ComboAttacks/STTComboAttackBase.h"
#include "AbilitySystem/Abilities/SkillAbilities/STTSkillAbilityBase.h"
#include "AbilitySystem/Abilities/UltimateSkillAbilities/STTUltimateSkillAbilityBase.h"

TArray<TSubclassOf<UGameplayAbility>> UCharacterAbilitiesDataAsset::GetDefaultAbilities() const
{
	//Array of all abilities to give
	TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGive;
	//Adding movement abilities
	for(TSubclassOf<UGameplayAbility> DefaultMovementAbility : DefaultMovementAbilities)
	{
		if(IsValid(DefaultMovementAbility))
		{
			AbilitiesToGive.Add(DefaultMovementAbility);
		}
	}
	//Adding normal attack abilities
	for (TSubclassOf<USTTComboAttackBase> DefaultNormalAttackAbility : DefaultNormalAttackAbilities)
	{
		if(IsValid(DefaultNormalAttackAbility))
		{
			AbilitiesToGive.Add(DefaultNormalAttackAbility);
		}
	}
	//Adding skill abilities
	if(IsValid(DefaultSkillAbility))
	{
		AbilitiesToGive.Add(DefaultSkillAbility);
	}
	//Adding Ultimate ability
	if(IsValid(DefaultUltimateSkillAbility))
	{
		AbilitiesToGive.Add(DefaultUltimateSkillAbility);
	}
	return AbilitiesToGive;
}
