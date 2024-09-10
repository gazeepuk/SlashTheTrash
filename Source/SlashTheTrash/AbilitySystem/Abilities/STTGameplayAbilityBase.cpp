// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/STTGameplayAbilityBase.h"
#include "AbilitySystemComponent.h"
#include "Characters/STTPlayerCharacter.h"

ASTTPlayerCharacter* USTTGameplayAbilityBase::GetSTTPlayerCharacterFromActorInfo() const
{
	AActor* Owner = GetActorInfo().AbilitySystemComponent->GetAvatarActor();
	return Owner ? Cast<ASTTPlayerCharacter>(Owner) : nullptr;
}
