// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Movement/JumpAbilityBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"

UJumpAbilityBase::UJumpAbilityBase()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
}

bool UJumpAbilityBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if(!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed);
	return Character && Character->CanJump();
}

void UJumpAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if(HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if(!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			return;
		}

		Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

		ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
		Character->Jump();
		if(UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Character))
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(JumpEffectClass, 1, EffectContext);

			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
		}
	}
}
