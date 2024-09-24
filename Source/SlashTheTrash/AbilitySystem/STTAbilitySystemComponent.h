// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "STTAbilitySystemComponent.generated.h"
/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API USTTAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void GiveCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);
};
