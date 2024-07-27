// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/STTGameplayAbilityBase.h"
#include "AbilitySystemComponent.h"
#include "Characters/STTCharacterBase.h"

ASTTCharacterBase* USTTGameplayAbilityBase::GetSTTCharacterFromActorInfo() const
{
	AActor* Owner = GetActorInfo().AbilitySystemComponent->GetOwner();
	return Owner ? Cast<ASTTCharacterBase>(Owner) : nullptr;
}
