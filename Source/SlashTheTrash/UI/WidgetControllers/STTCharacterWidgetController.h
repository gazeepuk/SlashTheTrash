// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/UltimateSkillAbilities/STTUltimateSkillAbilityBase.h"
#include "Characters/STTPlayerCharacter.h"
#include "Data/CharacterAbilitiesDataAsset.h"
#include "Data/CharacterDataAsset.h"
#include "UI/WidgetControllers/WidgetControllerBase.h"
#include "STTCharacterWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUltimateAbilityCommited, UGameplayAbility*, CommitedAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillAbilityCommited, UGameplayAbility*, CommitedAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpecialAbilityCommited, UGameplayAbility*, CommitedAbility);

class USTTSkillAbilityBase;
class USTTAttackAbilityBase;
/**
 * 
 */

UCLASS(BlueprintType)
class UCharacterWidgetControllerParams : public UWidgetControllerParams
{
	GENERATED_BODY()

public:
	virtual void InitParams(UAbilitySystemComponent* InASC, UAttributeSet* InAS, APlayerController* InPC, APlayerState* InPS) override
	{
		Super::InitParams(InASC, InAS, InPC, InPS);
		AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();
		ASTTPlayerCharacter* PlayerCharacter = Cast<ASTTPlayerCharacter>(AvatarActor);
		if(PlayerCharacter)
		{
			SkillAbilityClass = PlayerCharacter->CharacterDataAsset->CharacterAbilitiesDataAsset->GetSkillAbilityClass();
			UltimateAbilityClass = PlayerCharacter->CharacterDataAsset->CharacterAbilitiesDataAsset->GetUltimateSkillAbilityClass();
		}
	}
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<USTTSkillAbilityBase> SkillAbilityClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<USTTUltimateSkillAbilityBase> UltimateAbilityClass;
};

UCLASS(Blueprintable, BlueprintType)
class SLASHTHETRASH_API USTTCharacterWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:

	virtual void BindCallbacksToDependencies() override;
	virtual void SetWidgetControllerParams(UWidgetControllerParams* InParameters) override;
	
	//Get STTCharacter from AbilitySystemComponent AvatarActor
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ASTTCharacterBase* GetSTTCharacter() const;
	

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USTTAttackAbilityBase> SkillAbilityClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USTTAttackAbilityBase> UltimateAbilityClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USTTAttackAbilityBase> SpecialAbilityClass;

protected:
	//Broadcast delegates
	virtual void AbilityCommitted(UGameplayAbility* GameplayAbility) override;
	virtual void SkillAbilityCommitted(UGameplayAbility* GameplayAbility);
	virtual void UltimateAbilityCommitted(UGameplayAbility* GameplayAbility);
	virtual void SpecialAbilityCommitted(UGameplayAbility* GameplayAbility);
};
