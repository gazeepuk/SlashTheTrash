// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ComboAttacks/STTComboAttackBase.h"

#include "Characters/STTCharacterBase.h"

const FComboAttackStaticInfo& USTTComboAttackBase::GetComboAttackStaticInfo() const
{
	return ComboAttackStaticInfo;
}

void USTTComboAttackBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("USTTComboAttackBase slayed"));
}
