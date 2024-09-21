// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/STTCharacterWidgetController.h"

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
