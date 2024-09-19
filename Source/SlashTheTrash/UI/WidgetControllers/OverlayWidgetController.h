// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllers/WidgetControllerBase.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API UOverlayOpenWorldWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitValues() override;
	virtual void BindCallbacksToDependencies() override;
};
