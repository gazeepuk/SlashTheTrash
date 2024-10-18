// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/CombatInterface.h"
#include "Interfaces/DamageableInterface.h"
#include "STTCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDiedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetDamageDelegate, float, DamageValue);

struct FOnAttributeChangeData;
class UHealthBarOpenWorld;
class USTTUserWidgetBase;
class UWidgetComponent;
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
	
	//~Ability System
	UPROPERTY(Replicated)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(Transient, Replicated)
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	//~IDamageableInterface
	virtual void GetDamage_Implementation(FGameplayEffectSpec& DamageEffect) override;

	// Applies GameplayEffect to self by class and level
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	// bAlive Getter
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsAlive() const;
	// bAlive Setter
	void SetIsAlive(const bool bNewAlive);
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetWeaponVisibility(const bool bVisible);
	
protected:
	//Setup Default abilities and attributes
	//Gives default abilities
	virtual void GiveDefaultAbilities() const;
	//Applies all default effects
	UFUNCTION(BlueprintCallable)
	void ApplyDefaultAttributes();
	//Applies primary attributes
	UFUNCTION(BlueprintCallable)
	void ApplyPrimaryAttributes();
	//Applies Secondary attributes
	UFUNCTION(BlueprintCallable)
	void ApplySecondaryAttributes();
	
	//AbilityCommit delegate handle 
	FDelegateHandle OnCommitAbilityHandle;

	//Initialize ability system component
	UFUNCTION(BlueprintCallable)
	virtual void InitAbilitySystemComponent() {}

	//HealthBar
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated)
	TObjectPtr<UWidgetComponent> WidgetComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USTTUserWidgetBase> HealthBarWidgetClass;
	UPROPERTY()
	TObjectPtr<UHealthBarOpenWorld> HealthBarWidget;
	void InitHealthBarWidget();

	//Invokes on any health and max health changes
	void OnHealthChanged(const FOnAttributeChangeData& Data);
	//Invokes when get damage
	virtual void OnGetDamage(float DamageValue);
	//Invokes on death
	virtual void OnDied();

	//Health delegates
	UPROPERTY(BlueprintAssignable)
	FOnGetDamageDelegate GetDamageDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnDiedDelegate DiedDelegate;

	//Is character alive
	bool bAlive = true;
};
