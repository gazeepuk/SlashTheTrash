// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/STTCharacterBase.h"

#include "GameplayTagsManager.h"
#include "AbilitySystem/STTAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/STTGameplayAbilityBase.h"
#include "AbilitySystem/AttributeSet/STTCharacterAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Data/CharacterDataAsset.h"
#include "Data/CharacterAbilitiesDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "UI/Widgets/STTUserWidgetBase.h"
#include "UI/Widgets/OpenWorld/HealthBarOpenWorld.h"


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

	// Create HealthBar widget 
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	WidgetComponent->SetupAttachment(GetRootComponent());
}

void ASTTCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASTTCharacterBase, AbilitySystemComponent);
	DOREPLIFETIME(ASTTCharacterBase, AttributeSet);
	DOREPLIFETIME(ASTTCharacterBase, WidgetComponent);
}


void ASTTCharacterBase::InitHealthBarWidget()
{
	WidgetComponent->SetWidgetClass(HealthBarWidgetClass);
	WidgetComponent->InitWidget();
	UUserWidget* Widget = WidgetComponent->GetWidget();
	HealthBarWidget = Widget ? Cast<UHealthBarOpenWorld>(Widget) : nullptr;
	if(HealthBarWidget)
	{
		OnHealthChanged(FOnAttributeChangeData());
	}
}

void ASTTCharacterBase::OnHealthChanged(const FOnAttributeChangeData& Data) const
{
	const USTTCharacterAttributeSet* CharacterAttributeSet = GetAttributeSet() ? Cast<USTTCharacterAttributeSet>(GetAttributeSet()) : nullptr;
	if(HealthBarWidget && CharacterAttributeSet)
	{
		HealthBarWidget->UpdateHealthBar(CharacterAttributeSet->GetHealth(), CharacterAttributeSet->GetMaxHealth());
	}
}


void ASTTCharacterBase::ApplyDefaultAttributes()
{
	ApplyPrimaryAttributes();
	ApplySecondaryAttributes();
}

void ASTTCharacterBase::ApplyPrimaryAttributes()
{
	check(GetAbilitySystemComponent());
	check(CharacterDataAsset);
	check(CharacterDataAsset->DefaultPrimaryAttributesEffect);

	//Preparing default attributes effect
	FGameplayEffectContextHandle PrimaryContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	PrimaryContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle PrimarySpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(CharacterDataAsset->DefaultPrimaryAttributesEffect, GetPlayerLevel(), PrimaryContextHandle);

	const UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();

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
	
}

void ASTTCharacterBase::ApplySecondaryAttributes()
{
	checkf(GetAbilitySystemComponent(), TEXT("Ability system component is null"));
	checkf(CharacterDataAsset, TEXT("Charcter data asset is null"));
	checkf(CharacterDataAsset->DefaultSecondaryAttributesEffect, TEXT("Secondary attributes effect class is null"));
	ApplyEffectToSelf(CharacterDataAsset->DefaultSecondaryAttributesEffect, GetPlayerLevel());
}


void ASTTCharacterBase::GiveDefaultAbilities() const
{
	USTTAbilitySystemComponent* STTAbilitySystemComponent = CastChecked<USTTAbilitySystemComponent>(GetAbilitySystemComponent());
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

void ASTTCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}



