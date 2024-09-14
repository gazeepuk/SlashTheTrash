// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ComboAttacks/STTComboAttackBase.h"

USTTComboAttackBase::USTTComboAttackBase()
{
	bIsBlockingOtherAbilities = true;
	bIsCancelable = true;
}

const FComboAttackStaticInfo& USTTComboAttackBase::GetComboAttackStaticInfo() const
{
	return ComboAttackStaticInfo;
}

void USTTComboAttackBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if(!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle,ActorInfo,ActivationInfo, true, true);
		return;
	}
}
