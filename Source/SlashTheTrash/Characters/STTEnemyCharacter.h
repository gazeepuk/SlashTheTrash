// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/STTCharacterBase.h"
#include "STTEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API ASTTEnemyCharacter : public ASTTCharacterBase
{
	GENERATED_BODY()
public:
	ASTTEnemyCharacter();

	// Combat Interface
	virtual int32 GetPlayerLevel() override {return Level;}
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilitySystemComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level = 1;
};
