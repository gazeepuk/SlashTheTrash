// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/STTGameplayAbilityBase.h"
#include "AbilitySystemComponent.h"
#include "Characters/STTPlayerCharacter.h"

ASTTPlayerCharacter* USTTGameplayAbilityBase::GetSTTPlayerCharacterFromActorInfo() const
{
	AActor* Owner = GetActorInfo().AbilitySystemComponent->GetAvatarActor();
	return Owner ? Cast<ASTTPlayerCharacter>(Owner) : nullptr;
}

bool USTTGameplayAbilityBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	//Checking if STTCharacter is alive
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	const ASTTCharacterBase* STTCharacter = AvatarActor ? Cast<ASTTCharacterBase>(AvatarActor) : nullptr;
	const bool bCharacterAlive = STTCharacter ? STTCharacter->IsAlive() : true;

	//Can't activate an ability if character is dead
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) && bCharacterAlive;
}
