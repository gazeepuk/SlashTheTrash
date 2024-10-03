// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STTPlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API ASTTPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASTTPlayerController();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> STTMappingContext;
};
