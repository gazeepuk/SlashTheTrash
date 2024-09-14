// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "Characters/STTCharacterBase.h"
#include "STTPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API ASTTPlayerCharacter : public ASTTCharacterBase
{
	GENERATED_BODY()
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
	ASTTPlayerCharacter();

	UFUNCTION(BlueprintCallable)
	void ResetLastComboAttackClass();

	
protected:
	//ACharacter Interface
	virtual void BeginPlay() override;
	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;

	// Input
protected:

	//ACharacter interface
	//Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Input Actions Attacks
	//Combat actions
	UFUNCTION(BlueprintCallable)
	virtual void UseNormalAttack(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	virtual void UseHardAttack(const FInputActionValue& Value);
	//Skill action
	UFUNCTION(BlueprintCallable)
	virtual void UseSkill(const FInputActionValue& Value);
	//Ultimate skill action
	UFUNCTION(BlueprintCallable)
	virtual void UseUltimateSkill(const FInputActionValue& Value);
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	/** Called for jump input */
	void StartJumpInput(const FInputActionValue& Value);
	void StopJumpInput(const FInputActionValue& Value);

	virtual void Landed(const FHitResult& Hit) override;

	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	//Normal Attack Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> NormalAttackInputAction;
	//Hard Attack Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> HardAttackInputAction;
	//Move Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;
	//Look Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;
	//Jump Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;
	//Skill Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SkillAction;
	//Ultimate skill Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> UltimateSkillAction;
	
protected:
	//Camera
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> CameraBoomComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	//Attack Abilities Classes
	TSubclassOf<USTTComboAttackBase> LastComboAttackClass;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<USTTComboAttackBase>DefaultNormalAttackClass;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<USTTComboAttackBase>DefaultHardAttackClass;
		
	UFUNCTION()
	void OnAbilityCommited(UGameplayAbility* GameplayAbility);
	virtual void InitAbilitySystemComponent() override;
	
	//GameplayTags
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer JumpEffectTag;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag JumpEventTag;
};
