// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STTUserWidgetBase.generated.h"

class UWidgetControllerBase;
/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API USTTUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	//WidgetController Setter
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UWidgetControllerBase* InWidgetController);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UWidgetControllerBase* GetWidgetController() const {return WidgetController;}
	
	//Event invokes on SetWidgetController
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();

protected:
	TObjectPtr<UWidgetControllerBase> WidgetController;
};
