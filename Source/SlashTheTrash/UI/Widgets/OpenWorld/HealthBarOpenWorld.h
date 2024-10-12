// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/STTUserWidgetBase.h"
#include "HealthBarOpenWorld.generated.h"

/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API UHealthBarOpenWorld : public USTTUserWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);
};
