// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/STTEnemyCharacter.h"

#include "AbilitySystem/STTAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSet/STTCharacterAttributeSet.h"

ASTTEnemyCharacter::ASTTEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<USTTAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<USTTCharacterAttributeSet>(TEXT("AttributeSet"));
}

void ASTTEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystemComponent();
	GiveDefaultAbilities();
}

void ASTTEnemyCharacter::InitAbilitySystemComponent()
{
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}
