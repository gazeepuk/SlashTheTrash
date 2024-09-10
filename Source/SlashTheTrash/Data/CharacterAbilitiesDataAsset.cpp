// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CharacterAbilitiesDataAsset.h"

#include "Abilities/GameplayAbility.h"

const TArray<TSubclassOf<UGameplayAbility>>& UCharacterAbilitiesDataAsset::GetDefaultAbilities() const
{
	return DefaultAbilities;
}
