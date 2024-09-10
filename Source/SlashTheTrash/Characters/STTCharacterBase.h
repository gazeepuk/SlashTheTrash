// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/DamageableInterface.h"
#include "STTCharacterBase.generated.h"

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
class SLASHTHETRASH_API ASTTCharacterBase : public ACharacter, public IAbilitySystemInterface, public IDamageableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTTCharacterBase();

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
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(Transient)
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	//~IDamageableInterface
	virtual void GetDamage_Implementation(FGameplayEffectSpec& DamageEffect) override;

protected:
	virtual void GiveDefaultAbilities() const;
	UFUNCTION(BlueprintCallable)
	void ApplyDefaultAttributes();
	
	UFUNCTION(BlueprintCallable)
	virtual void InitAbilitySystemComponent() {}
};
