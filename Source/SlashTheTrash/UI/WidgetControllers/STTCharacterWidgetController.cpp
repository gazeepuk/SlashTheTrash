// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/STTCharacterWidgetController.h"

#include "AbilitySystem/Abilities/SkillAbilities/STTSkillAbilityBase.h"
#include "Characters/STTCharacterBase.h"
#include "Data/CharacterDataAsset.h"
#include "Data/CharacterAbilitiesDataAsset.h"


ASTTCharacterBase* USTTCharacterWidgetController::GetSTTCharacter() const
{
	if(AbilitySystemComponent)
	{
		AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();
		return AvatarActor ? Cast<ASTTCharacterBase>(AvatarActor) : nullptr;
	}
	return nullptr;
}

TSubclassOf<USTTUltimateSkillAbilityBase> USTTCharacterWidgetController::GetUltiamteAbilityClass()
{
	ASTTCharacterBase* STTCharacter = GetSTTCharacter();
	if(STTCharacter)
	{
		if(STTCharacter->CharacterDataAsset && STTCharacter->CharacterDataAsset->CharacterAbilitiesDataAsset)
		{
			return STTCharacter->CharacterDataAsset->CharacterAbilitiesDataAsset->GetUltimateSkillAbilityClass();
		}
	}
	return nullptr;
}

TSubclassOf<USTTSkillAbilityBase> USTTCharacterWidgetController::GetSkillAbilityClass()
{
	ASTTCharacterBase* STTCharacter = GetSTTCharacter();
	if(STTCharacter)
	{
		if(STTCharacter->CharacterDataAsset && STTCharacter->CharacterDataAsset->CharacterAbilitiesDataAsset)
		{
			return STTCharacter->CharacterDataAsset->CharacterAbilitiesDataAsset->GetSkillAbilityClass();
		}
	}
	return nullptr;
}

FAbilityUIInfo USTTCharacterWidgetController::GetAbilityUIInfoByClass(TSubclassOf<USTTAttackAbilityBase> AttackAbilityClass)
{
	return AttackAbilityClass.GetDefaultObject()->GetAbilityUIInfo();
}

void USTTCharacterWidgetController::AbilityCommited(UGameplayAbility* GameplayAbility)
{
	if(GameplayAbility)
	{
		OnGameplayAbilityCommited.Broadcast(GameplayAbility);
		if(GetUltiamteAbilityClass() && GameplayAbility->IsA(GetUltiamteAbilityClass()))
		{
			UltimateAbilityCommited(GameplayAbility);
		}
		if(GetSkillAbilityClass() && GameplayAbility->IsA(GetSkillAbilityClass()))
		{
			SkillAbilityCommited(GameplayAbility);
		}
		if(SpecialAbilityClass && GameplayAbility->IsA(SpecialAbilityClass))
		{
			SpecialAbilityCommited(GameplayAbility);
		}
	}
}

void USTTCharacterWidgetController::SkillAbilityCommited(UGameplayAbility* GameplayAbility)
{
	OnSkillAbilityCommited.Broadcast(GameplayAbility);
}

void USTTCharacterWidgetController::UltimateAbilityCommited(UGameplayAbility* GameplayAbility)
{
	OnUltimateAbilityCommited.Broadcast(GameplayAbility);
}

void USTTCharacterWidgetController::SpecialAbilityCommited(UGameplayAbility* GameplayAbility)
{
	if(GameplayAbility && SpecialAbilityClass && GameplayAbility->IsA(SpecialAbilityClass))
	{
		OnSpecialAbilityCommited.Broadcast(GameplayAbility);
	}
}
