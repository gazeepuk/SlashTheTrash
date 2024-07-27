// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CharacterAbilitiesDataAsset.h"

const TArray<TSubclassOf<USTTGameplayAbilityBase>>& UCharacterAbilitiesDataAsset::GetDefaultAbilities() const
{
	return DefaultAbilities;
}
