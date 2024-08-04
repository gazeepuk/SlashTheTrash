// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STT_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API USTT_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;
};
