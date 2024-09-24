// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/UltimateSkillAbilities/STTUltimateSkillAbilityBase.h"
#include "UI/WidgetControllers/WidgetControllerBase.h"
#include "STTCharacterWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUltimateAbilityCommited, UGameplayAbility*, CommitedAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillAbilityCommited, UGameplayAbility*, CommitedAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpecialAbilityCommited, UGameplayAbility*, CommitedAbility);

class USTTSkillAbilityBase;
class USTTAttackAbilityBase;
class ASTTCharacterBase;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SLASHTHETRASH_API USTTCharacterWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	//Get STTCharacter from AbilitySystemComponent AvatarActor
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ASTTCharacterBase* GetSTTCharacter() const;

	//Get abilities from STTCharacter
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<USTTUltimateSkillAbilityBase> GetUltiamteAbilityClass();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<USTTSkillAbilityBase> GetSkillAbilityClass();

	//Get FAbilityUIInfo struct by ability class
	UFUNCTION(BlueprintCallable,BlueprintType)
	FAbilityUIInfo GetAbilityUIInfoByClass(TSubclassOf<USTTAttackAbilityBase> AttackAbilityClass);

	//Abilities delegates
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FUltimateAbilityCommited OnUltimateAbilityCommited;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FSkillAbilityCommited OnSkillAbilityCommited;
	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FSpecialAbilityCommited OnSpecialAbilityCommited;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> SpecialAbilityClass;
	
protected:
	//Broadcast delegates
	virtual void AbilityCommited(UGameplayAbility* GameplayAbility) override;
	virtual void SkillAbilityCommited(UGameplayAbility* GameplayAbility);
	virtual void UltimateAbilityCommited(UGameplayAbility* GameplayAbility);
	virtual void SpecialAbilityCommited(UGameplayAbility* GameplayAbility);
};
