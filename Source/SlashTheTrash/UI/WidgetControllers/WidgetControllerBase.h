// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/AttributeSet/STTCharacterAttributeSet.h"
#include "WidgetControllerBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

//AttributeSet values Delegates
//Health
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthChanged, float, NewHealth, float, OldHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMaxHealthChanged, float, NewMaxHealth, float, OldMaxHealth);
//Ultimate Energy
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUltimateEnergyChanged, float, NewUltimateEnergy, float, OldUltimateEnergy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMaxUltimateEnergyChanged, float, NewMaxUltimateEnergy, float, OldMaxUltimateEnergy);
//Attack
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttackChanged, float, NewAttack, float, OldAttack);
//Defence
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDefenceChanged, float, NewDefence, float, OldDefence);
//Energy Regeneration
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnergyRegenChanged, float, NewEnergyRegen, float, OldEnergyRegen);
//Critical Damage
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCritDamageChanged, float, NewCritDamage, float, OldCritDamage);
//Critical Rate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCritRateChanged, float, NewCritRate, float, OldCritRate);
//Gameplay ability commited delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameplayAbilityCommited, const UGameplayAbility*, ActivatedAbility);

UCLASS(BlueprintType, Blueprintable)
class SLASHTHETRASH_API UWidgetControllerParams : public UObject
{
	GENERATED_BODY()

public:
	virtual void InitParams(UAbilitySystemComponent* InASC, UAttributeSet* InAS, APlayerController* InPC, APlayerState* InPS);
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
	virtual void SetWidgetControllerParams(UWidgetControllerParams* InParameters);
	//Broadcast initial values
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitValues(){}
	//Bind callbacks
	UFUNCTION(BlueprintCallable)
	virtual void BindCallbacksToDependencies(){}

	USTTCharacterAttributeSet* GetSTTAttributeSet() const {return CastChecked<USTTCharacterAttributeSet>(AttributeSet);}
	
	//Attribute values delegates
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FMaxHealthChanged OnMaxHealthChangedDelegate;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FHealthChanged OnHealthChangedDelegate;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FMaxUltimateEnergyChanged OnMaxUltimateEnergyChangedDelegate;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FUltimateEnergyChanged OnUltimateEnergyChangedDelegate;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FAttackChanged OnAttackChangedDelegate;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FDefenceChanged OnDefenceChangedDelegate;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FEnergyRegenChanged OnEnergyRegenChangedDelegate;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FCritDamageChanged OnCritDamageChangedDelegate;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FCritRateChanged OnCritRateChangedDelegate;
	//GameplayAbility commited delegate
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FGameplayAbilityCommited OnGameplayAbilityCommited;
	
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

	//GameplayAttributeValueChangeDelegate callbacks
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	virtual void HealthChanged(const FOnAttributeChangeData& Data) const;
	virtual void MaxUltimateEnergyChanged(const FOnAttributeChangeData& Data) const;
	virtual void UltimateEnergyChanged(const FOnAttributeChangeData& Data) const;
	virtual void AttackChanged(const FOnAttributeChangeData& Data) const;
	virtual void DefenceChanged(const FOnAttributeChangeData& Data) const;
	virtual void EnergyRegenChanged(const FOnAttributeChangeData& Data) const;
	virtual void CritDamageChanged(const FOnAttributeChangeData& Data) const;
	virtual void CritRateChanged(const FOnAttributeChangeData& Data) const;
	virtual void AbilityCommitted(UGameplayAbility* GameplayAbility);
};
