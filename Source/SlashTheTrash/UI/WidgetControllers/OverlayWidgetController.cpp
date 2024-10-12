// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/OverlayWidgetController.h"

#include "AbilitySystem/AttributeSet/STTCharacterAttributeSet.h"

void UOverlayOpenWorldWidgetController::BroadcastInitValues()
{
	USTTCharacterAttributeSet* STTAttributeSet = GetSTTAttributeSet();

	//Broadcast health attributes
	OnMaxHealthChangedDelegate.Broadcast(STTAttributeSet->GetMaxHealth(), STTAttributeSet->GetMaxHealth());
	OnHealthChangedDelegate.Broadcast(STTAttributeSet->GetHealth(), STTAttributeSet->GetHealth());
	//Broadcast ultimate energy attributes
	OnMaxUltimateEnergyChangedDelegate.Broadcast(STTAttributeSet->GetMaxUltimateEnergy(), STTAttributeSet->GetMaxUltimateEnergy());
	OnUltimateEnergyChangedDelegate.Broadcast(STTAttributeSet->GetUltimateEnergy(), STTAttributeSet->GetUltimateEnergy());
}

void UOverlayOpenWorldWidgetController::BindCallbacksToDependencies()
{
	if(AbilitySystemComponent && AttributeSet)
	{
		USTTCharacterAttributeSet* STTAttributeSet = CastChecked<USTTCharacterAttributeSet>(AttributeSet);

		//Binding health attributes
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(STTAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::HealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(STTAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::MaxHealthChanged);
		//Binding ultimate energy attributes
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(STTAttributeSet->GetUltimateEnergyAttribute()).AddUObject(this, &ThisClass::UltimateEnergyChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(STTAttributeSet->GetMaxUltimateEnergyAttribute()).AddUObject(this, &ThisClass::MaxUltimateEnergyChanged);
		//Binding GameplayAbility activation
		AbilitySystemComponent->AbilityCommittedCallbacks.AddUObject(this, &ThisClass::AbilityCommitted);
	}
}
