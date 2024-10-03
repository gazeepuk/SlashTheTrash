// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStates/STTPlayerStateBase.h"

#include "AbilitySystem/STTAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSet/STTCharacterAttributeSet.h"
#include "Net/UnrealNetwork.h"

ASTTPlayerStateBase::ASTTPlayerStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<USTTAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<USTTCharacterAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100;
}

void ASTTPlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASTTPlayerStateBase, Level);
}

UAbilitySystemComponent* ASTTPlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ASTTPlayerStateBase::GetAttributeSet() const
{
	return AttributeSet;
}

void ASTTPlayerStateBase::OnRep_Level(int32 OldLevel)
{
}
