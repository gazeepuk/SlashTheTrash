// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AttackAbilityBase.h"

#include "AbilitySystemComponent.h"

void UAttackAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ThisClass::CommitAbility(Handle, ActorInfo, ActivationInfo);
}
