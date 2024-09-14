// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/STTAttackAbilityBase.h"

#include "AbilitySystemComponent.h"
#include "Interfaces/DamageableInterface.h"


void USTTAttackAbilityBase::ApplyEffectToTracedTarget()
{
	//Check if AbilitySystemComponent is valid. Return if it's not
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if(!IsValid(AbilitySystemComponent))
	{
		return;
	}

	//Getting traced targets
	TArray<AActor*> Targets = TraceDamageableActors();
	//Applying Effect throw the loop 
	for (AActor* Target : Targets)
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(AbilityEffectClass, 1, EffectContextHandle);
		
		if(IDamageableInterface* DamageableActor = Cast<IDamageableInterface>(Target))
		{
			DamageableActor->Execute_GetDamage(Target, *EffectSpecHandle.Data.Get());
			RestoreEnergyOnce();
		}
	}
}

void USTTAttackAbilityBase::ApplyEffectToSelf()
{
	//Check if AbilitySystemComponent is valid. Return if it's not
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if(!IsValid(AbilitySystemComponent))
	{
		return;
	}
	
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(AbilityEffectClass, 1, EffectContextHandle);
	//Applying effect to self
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	//Restoring energy if applied successfully 
	if(ActiveGameplayEffectHandle.WasSuccessfullyApplied())
	{
		RestoreEnergyOnce();
	}
}

void USTTAttackAbilityBase::PerformAbilityAction()
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if(!AbilityEffectClass || !AbilitySystemComponent)
	{
		return;
	}

	//Choosing Target
 	if(bTargetIsSelf)
	{
		ApplyEffectToSelf();
	}
	else
	{
		ApplyEffectToTracedTarget();
	}
}

void USTTAttackAbilityBase::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	ResetRestoreEnergyOnce();
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
