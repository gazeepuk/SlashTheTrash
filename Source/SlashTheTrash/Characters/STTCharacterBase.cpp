// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/STTCharacterBase.h"

#include "GameplayTagsManager.h"
#include "AbilitySystem/STTAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/STTGameplayAbilityBase.h"
#include "AbilitySystem/AttributeSet/STTCharacterAttributeSet.h"
#include "Data/CharacterDataAsset.h"
#include "Data/CharacterAbilitiesDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"




// Sets default values
ASTTCharacterBase::ASTTCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	
}


// Called when the game starts or when spawned
void ASTTCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}


void ASTTCharacterBase::ApplyDefaultAttributes()
{
	check(IsValid(GetAbilitySystemComponent()));
	check(CharacterDataAsset);
	check(CharacterDataAsset->DefaultPrimaryAttributesEffect);
	check(CharacterDataAsset->DefaultSecondaryAttributesEffect);

	//Preparing default attributes effect
	FGameplayEffectContextHandle PrimaryContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle PrimarySpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(CharacterDataAsset->DefaultPrimaryAttributesEffect, 1, PrimaryContextHandle);

	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();

	//Setup for SetByCaller
	PrimarySpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetMaxHealth"), CharacterDataAsset->DefaultAttributes.MaxHealth);
	PrimarySpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetMaxUltimateEnergy"), CharacterDataAsset->DefaultAttributes.MaxUltimateEnergy);
	PrimarySpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetAttack"), CharacterDataAsset->DefaultAttributes.Attack);
	PrimarySpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetDefence"), CharacterDataAsset->DefaultAttributes.Defence);
	PrimarySpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetCritRate"), CharacterDataAsset->DefaultAttributes.CritRate);
	PrimarySpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetCritDmg"), CharacterDataAsset->DefaultAttributes.CritDmg);
	PrimarySpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetEnergyRegen"), CharacterDataAsset->DefaultAttributes.EnergyRegen);

	//Applying default attributes effect
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*PrimarySpecHandle.Data.Get());

	//Preparing secondary attributes effect
	FGameplayEffectContextHandle SecondaryContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SecondarySpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(CharacterDataAsset->DefaultSecondaryAttributesEffect, 1, SecondaryContextHandle);
	//Applying secondary attributes effect
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SecondarySpecHandle.Data.Get());
}


void ASTTCharacterBase::GiveDefaultAbilities() const
{
	USTTAbilitySystemComponent* STTAbilitySystemComponent = CastChecked<USTTAbilitySystemComponent>(GetAbilitySystemComponent(), ECastCheckedType::NullAllowed);
	if(!HasAuthority() || !STTAbilitySystemComponent || !IsValid(CharacterDataAsset) || !IsValid(CharacterDataAsset->CharacterAbilitiesDataAsset))
	{
		return;
	}

	//Give default abilities
	STTAbilitySystemComponent->GiveCharacterAbilities(CharacterDataAsset->CharacterAbilitiesDataAsset->GetDefaultAbilities());
}


UAbilitySystemComponent* ASTTCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ASTTCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void ASTTCharacterBase::GetDamage_Implementation(FGameplayEffectSpec& DamageEffect)
{
	if(IsValid(GetAbilitySystemComponent()))
	{
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(DamageEffect, GetAbilitySystemComponent());
	}
}



