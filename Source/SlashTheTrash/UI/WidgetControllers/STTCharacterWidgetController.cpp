// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/STTCharacterWidgetController.h"

#include "AbilitySystem/Abilities/SkillAbilities/STTSkillAbilityBase.h"
#include "Characters/STTCharacterBase.h"


void USTTCharacterWidgetController::BindCallbacksToDependencies()
{
	AbilitySystemComponent->AbilityCommittedCallbacks.AddUObject(this, &USTTCharacterWidgetController::AbilityCommitted);	
}

void USTTCharacterWidgetController::SetWidgetControllerParams(UWidgetControllerParams* InParameters)
{
	Super::SetWidgetControllerParams(InParameters);
	
	const UCharacterWidgetControllerParams* CharacterWidgetControllerParams = Cast<UCharacterWidgetControllerParams>(InParameters);
	if(CharacterWidgetControllerParams)
	{
		SkillAbilityClass = CharacterWidgetControllerParams->SkillAbilityClass;
		UltimateAbilityClass = CharacterWidgetControllerParams->UltimateAbilityClass;
	}
}

ASTTCharacterBase* USTTCharacterWidgetController::GetSTTCharacter() const
{
	if(AbilitySystemComponent)
	{
		AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();
		return AvatarActor ? Cast<ASTTCharacterBase>(AvatarActor) : nullptr;
	}
	return nullptr;
}



FAbilityUIInfo USTTCharacterWidgetController::GetAbilityUIInfoByClass(TSubclassOf<USTTAttackAbilityBase> AttackAbilityClass)
{
	if(AttackAbilityClass)
	{
		return AttackAbilityClass.GetDefaultObject()->GetAbilityUIInfo();
	}
	return FAbilityUIInfo();
}

void USTTCharacterWidgetController::AbilityCommitted(UGameplayAbility* GameplayAbility)
{
	if(GameplayAbility)
	{
		OnGameplayAbilityCommited.Broadcast(GameplayAbility);
		if(UltimateAbilityClass && GameplayAbility->IsA(UltimateAbilityClass))
		{
			UltimateAbilityCommitted(GameplayAbility);
		}
		if(SkillAbilityClass && GameplayAbility->IsA(SkillAbilityClass))
		{
			SkillAbilityCommitted(GameplayAbility);
		}
		if(SpecialAbilityClass && GameplayAbility->IsA(SpecialAbilityClass))
		{
			SpecialAbilityCommitted(GameplayAbility);
		}
	}
}

void USTTCharacterWidgetController::SkillAbilityCommitted(UGameplayAbility* GameplayAbility)
{
	OnSkillAbilityCommited.Broadcast(GameplayAbility);
}

void USTTCharacterWidgetController::UltimateAbilityCommitted(UGameplayAbility* GameplayAbility)
{
	OnUltimateAbilityCommited.Broadcast(GameplayAbility);
}

void USTTCharacterWidgetController::SpecialAbilityCommitted(UGameplayAbility* GameplayAbility)
{
	OnSpecialAbilityCommited.Broadcast(GameplayAbility);
}
