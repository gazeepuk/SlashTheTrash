// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/STTUserWidgetBase.h"

void USTTUserWidgetBase::SetWidgetController(UWidgetControllerBase* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSet();
}
