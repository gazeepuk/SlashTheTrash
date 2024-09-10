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
	check(CharacterDataAsset->DefaultGameplayEffect);
	
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(CharacterDataAsset->DefaultGameplayEffect, 1, ContextHandle);

	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();

	//Setup for SetByCaller
	SpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetMaxHealth"), CharacterDataAsset->DefaultAttributes.MaxHealth);
	SpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetMaxUltimateEnergy"), CharacterDataAsset->DefaultAttributes.MaxUltimateEnergy);
	SpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetAttack"), CharacterDataAsset->DefaultAttributes.Attack);
	SpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetDefence"), CharacterDataAsset->DefaultAttributes.Defence);
	SpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetCritRate"), CharacterDataAsset->DefaultAttributes.CritRate);
	SpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetCritDmg"), CharacterDataAsset->DefaultAttributes.CritDmg);
	SpecHandle.Data->SetSetByCallerMagnitude(TagsManager.RequestGameplayTag("Event.Effect.SetEnergyRegen"), CharacterDataAsset->DefaultAttributes.EnergyRegen);
		
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
	
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



