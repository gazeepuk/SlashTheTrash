// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterDataAsset.generated.h"

class UGameplayEffect;
class UCharacterAnimationsDataAsset;
class UCharacterAbilitiesDataAsset;
/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API UCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const TObjectPtr<UCharacterAbilitiesDataAsset> CharacterAbilitiesDataAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const TObjectPtr<UCharacterAnimationsDataAsset> CharacterAnimationsDataAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const TSubclassOf<UGameplayEffect> DefaultGameplayEffect;
};
