// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterAnimationsDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API UCharacterAnimationsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UAnimSequenceBase> IdleAnimation;

	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UAnimMontage> DeathAnimation;

	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UAnimMontage> GetDamageAnimation;
	
	UPROPERTY(EditDefaultsOnly)
	const TObjectPtr<UBlendSpace> MovementBlendSpace;

};
