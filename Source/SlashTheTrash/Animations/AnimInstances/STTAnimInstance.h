// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "STTAnimInstance.generated.h"

class UCharacterAnimationsDataAsset;
/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API USTTAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UCharacterAnimationsDataAsset* GetAnimationsDataAsset() const;
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	UBlendSpace* GetMovementBlendSpace() const;
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	UAnimMontage* GetDamageAnimation() const;
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	UAnimMontage* DiedAnimation() const;
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	UAnimSequenceBase* GetIdleAnimation() const;
};
