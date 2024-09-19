// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/WidgetControllerBase.h"

void UWidgetControllerBase::SetWidgetControllerParams(const FWidgetControllerParams& InParameters)
{
	AbilitySystemComponent = InParameters.AbilitySystemComponent;
	AttributeSet = InParameters.AttributeSet;
	PlayerController = InParameters.PlayerController;
	PlayerState = InParameters.PlayerState;
}

void UWidgetControllerBase::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
}

void UWidgetControllerBase::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
}

void UWidgetControllerBase::MaxUltimateEnergyChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxUltimateEnergyChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
}

void UWidgetControllerBase::UltimateEnergyChanged(const FOnAttributeChangeData& Data) const
{
	OnUltimateEnergyChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
}

void UWidgetControllerBase::AttackChanged(const FOnAttributeChangeData& Data) const
{
	OnAttackChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
}

void UWidgetControllerBase::DefenceChanged(const FOnAttributeChangeData& Data) const
{
	OnDefenceChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
}

void UWidgetControllerBase::EnergyRegenChanged(const FOnAttributeChangeData& Data) const
{
	OnEnergyRegenChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
}

void UWidgetControllerBase::CritDamageChanged(const FOnAttributeChangeData& Data) const
{
	OnCritDamageChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
}

void UWidgetControllerBase::CritRateChanged(const FOnAttributeChangeData& Data) const
{
	OnCritDamageChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
}
