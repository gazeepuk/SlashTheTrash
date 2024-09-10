// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/STTAbilitySystemComponent.h"

void USTTAbilitySystemComponent::GiveCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (const TSubclassOf<UGameplayAbility> Ability : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		GiveAbility(AbilitySpec);
	}
}
