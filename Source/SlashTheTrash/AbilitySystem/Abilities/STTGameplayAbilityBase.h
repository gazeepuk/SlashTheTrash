// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "STTGameplayAbilityBase.generated.h"

class ASTTCharacterBase;
/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API USTTGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ASTTCharacterBase* GetSTTCharacterFromActorInfo() const;

	UFUNCTION(BlueprintImplementableEvent)
	TArray<AActor*> TraceDamageableActors();
};
