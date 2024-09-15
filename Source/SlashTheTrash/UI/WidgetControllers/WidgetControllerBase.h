// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UObject/NoExportTypes.h"
#include "WidgetControllerBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType, Blueprintable)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	//Default constructor
	FWidgetControllerParams(){}
	//Constructor with parameters
	FWidgetControllerParams(UAbilitySystemComponent* InASC, UAttributeSet* InAS, APlayerController* InPC, APlayerState* InPS)
	:AbilitySystemComponent(InASC),AttributeSet(InAS),PlayerController(InPC),PlayerState(InPS){}
	
	//Parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState;
};
/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API UWidgetControllerBase : public UObject
{
	GENERATED_BODY()
public:
	//Set params values 
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& InParameters);
protected:
	//Params
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<APlayerState> PlayerState;
};
