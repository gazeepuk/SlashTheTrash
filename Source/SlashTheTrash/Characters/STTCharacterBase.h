// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "InputActionValue.h"
#include "STTCharacterBase.generated.h"

class UGameplayAbility;
class UInputAction;
class UInputMappingContext;
class USTTComboAttackBase;
class UCharacterDataAsset;
class USTTCharacterAttributeSet;
class USTTAbilitySystemComponent;

UCLASS()
class SLASHTHETRASH_API ASTTCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTTCharacterBase();

	//~IAbilitySystemInterface interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const TObjectPtr<UCharacterDataAsset> CharacterDataAsset;

protected:

	//~ACharacter interface
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void PostInitializeComponents() override;
	
	//~Ability System
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USTTAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(Transient)
	TObjectPtr<USTTCharacterAttributeSet> AttributeSet;
	
	TSubclassOf<USTTComboAttackBase> LastComboAttackClass;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<USTTComboAttackBase>DefaultNormalAttackClass;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<USTTComboAttackBase>DefaultHardAttackClass;

	UFUNCTION()
	void OnAbilityCommited(UGameplayAbility* GameplayAbility);
protected:
	//~APawn interface
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Input Actions Attacks
	UFUNCTION(BlueprintCallable)
	virtual void UseNormalAttack(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	virtual void UseHardAttack(const FInputActionValue& Value);
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Normal Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> NormalAttackInputAction;
	/** Hard Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> HardAttackInputAction;
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;
};
