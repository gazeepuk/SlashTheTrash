// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/STTAttackAbilityBase.h"

#include "AbilitySystemComponent.h"
#include "Interfaces/DamageableInterface.h"


void USTTAttackAbilityBase::PerformAbilityAction()
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if(!AttackEffectClass || !AbilitySystemComponent)
	{
		return;
	}
	
	TArray<AActor*> Targets = TraceDamageableActors();
	for (AActor* Target : Targets)
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(AttackEffectClass, 1, EffectContextHandle);
		if(IDamageableInterface* DamageableActor = Cast<IDamageableInterface>(Target))
		{
			DamageableActor->Execute_GetDamage(Target, *EffectSpecHandle.Data.Get());
			RestoreEnergyOnce();
		}
	}
}

void USTTAttackAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	if(!ThisClass::CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}
	ResetRestoreEnergyOnce();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USTTAttackAbilityBase::RestoreEnergy()
{
	if(!bRestoreEnergy)
	{
		return;
	}
	
	if(UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
		AbilitySystemComponent && IsValid(RestoreBattleEnergyEffectClass))
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(RestoreBattleEnergyEffectClass, 1, EffectContextHandle);
		EffectSpecHandle.Data->SetSetByCallerMagnitude(BattleEnergyRegenTag, EnergyRegenAmount);
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void USTTAttackAbilityBase::RestoreEnergyOnce()
{
	if(bCanRestoreEnergyOnce)
	{
		RestoreEnergy();
		bCanRestoreEnergyOnce = false;
	}
}

void USTTAttackAbilityBase::ResetRestoreEnergyOnce()
{
	bCanRestoreEnergyOnce = true;
}
