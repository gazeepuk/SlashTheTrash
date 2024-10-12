// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/HealthBarWidgetController.h"

void UHealthBarWidgetController::BroadcastInitValues()
{
	USTTCharacterAttributeSet* STTAttributeSet = GetSTTAttributeSet();

	//Broadcast health attributes
	OnMaxHealthChangedDelegate.Broadcast(STTAttributeSet->GetMaxHealth(), STTAttributeSet->GetMaxHealth());
	OnHealthChangedDelegate.Broadcast(STTAttributeSet->GetHealth(), STTAttributeSet->GetHealth());
}

void UHealthBarWidgetController::BindCallbacksToDependencies()
{
	if(AbilitySystemComponent && AttributeSet)
	{
		USTTCharacterAttributeSet* STTAttributeSet = CastChecked<USTTCharacterAttributeSet>(AttributeSet);

		//Binding health attributes
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(STTAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::HealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(STTAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::MaxHealthChanged);
	}
}
