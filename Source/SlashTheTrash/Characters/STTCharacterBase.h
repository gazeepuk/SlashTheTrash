// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/CombatInterface.h"
#include "Interfaces/DamageableInterface.h"
#include "STTCharacterBase.generated.h"

class USTTUltimateSkillAbilityBase;
class USTTSkillAbilityBase;
class UAttributeSet;
class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;
class UGameplayAbility;
class UInputAction;
class UInputMappingContext;
class USTTComboAttackBase;
class UCharacterDataAsset;
class USTTCharacterAttributeSet;
class USTTAbilitySystemComponent;

UCLASS(Abstract)
class SLASHTHETRASH_API ASTTCharacterBase : public ACharacter, public IAbilitySystemInterface, public IDamageableInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTTCharacterBase();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//~IAbilitySystemInterface interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const TObjectPtr<UCharacterDataAsset> CharacterDataAsset;

protected:

	//~ACharacter interface
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//~Ability System
	UPROPERTY(Replicated)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(Transient, Replicated)
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	//~IDamageableInterface
	virtual void GetDamage_Implementation(FGameplayEffectSpec& DamageEffect) override;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
protected:
	//Setup Default abilities and attributes
	//Gives default abilities
	virtual void GiveDefaultAbilities() const;
	//Applies all default effects
	UFUNCTION(BlueprintCallable)
	void ApplyDefaultAttributes();
	//Applies primary attributes
	UFUNCTION(BlueprintCallable)
	void ApplyPriamryAttributes();
	//Applies Secondary attributes
	UFUNCTION(BlueprintCallable)
	void ApplySecondaryAttributes();
	
	//AbilityCommit delegate handle 
	FDelegateHandle OnCommitAbilityHandle;
	
	UFUNCTION(BlueprintCallable)
	virtual void InitAbilitySystemComponent() {}
};
