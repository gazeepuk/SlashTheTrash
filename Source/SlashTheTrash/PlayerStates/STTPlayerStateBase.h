// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/CombatInterface.h"
#include "STTPlayerStateBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API ASTTPlayerStateBase : public APlayerState, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ASTTPlayerStateBase();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual int32 GetPlayerLevel() override {return Level;}
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const;
	
protected:
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	TObjectPtr<UAttributeSet> AttributeSet;

private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;
	
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
};

