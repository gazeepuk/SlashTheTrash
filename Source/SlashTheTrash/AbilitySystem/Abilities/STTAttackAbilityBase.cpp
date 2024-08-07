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
			DamageableActor->GetDamage(*EffectSpecHandle.Data.Get());
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
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
