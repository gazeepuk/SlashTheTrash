// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/WidgetControllerBase.h"

void UWidgetControllerBase::SetWidgetControllerParams(const FWidgetControllerParams& InParameters)
{
	AbilitySystemComponent = InParameters.AbilitySystemComponent;
	AttributeSet = InParameters.AttributeSet;
	PlayerController = InParameters.PlayerController;
	PlayerState = InParameters.PlayerState;
}
