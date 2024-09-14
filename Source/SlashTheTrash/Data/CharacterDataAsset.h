// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterDataAsset.generated.h"

class UGameplayEffect;
class UCharacterAnimationsDataAsset;
class UCharacterAbilitiesDataAsset;

USTRUCT(BlueprintType, Blueprintable)
struct FDefaultCharacterAttributes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1))
	float MaxHealth = 1.f;
	UPROPERTY(EditAnywhere, meta = (ClampMin = 1))
	float MaxUltimateEnergy = 1.f;
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	float Attack = 0.f;
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	float Defence = 0.f;
	
	//Scale as multipliers 
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	float CritRate = 0.f;
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	float CritDmg = 0.f;
	UPROPERTY(EditAnywhere, meta = (ClampMin = 1))
	float EnergyRegen = 1.f;
};
/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API UCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	//Data asset with default abilities
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const TObjectPtr<UCharacterAbilitiesDataAsset> CharacterAbilitiesDataAsset;
	//Data asset with character's animations 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const TObjectPtr<UCharacterAnimationsDataAsset> CharacterAnimationsDataAsset;
	//Effects to apply default attributes
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const TSubclassOf<UGameplayEffect> DefaultPrimaryAttributesEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const TSubclassOf<UGameplayEffect> DefaultSecondaryAttributesEffect;
	//Structure with default attributes values 
	UPROPERTY(EditDefaultsOnly)
	FDefaultCharacterAttributes DefaultAttributes;
};
