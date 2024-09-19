// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "STTCharacterAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class SLASHTHETRASH_API USTTCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	//Setup replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//Attributes
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USTTCharacterAttributeSet, MaxHealth)
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USTTCharacterAttributeSet, Health)
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_Attack)
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(USTTCharacterAttributeSet, Attack)
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_Defence)
	FGameplayAttributeData Defence;
	ATTRIBUTE_ACCESSORS(USTTCharacterAttributeSet, Defence)
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_EnergyRegen)
	FGameplayAttributeData EnergyRegen;
	ATTRIBUTE_ACCESSORS(USTTCharacterAttributeSet, EnergyRegen)
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_CritRate)
	FGameplayAttributeData CritRate;
	ATTRIBUTE_ACCESSORS(USTTCharacterAttributeSet, CritRate)
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_CritDamage)
	FGameplayAttributeData CritDamage;
	ATTRIBUTE_ACCESSORS(USTTCharacterAttributeSet, CritDamage)
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_MaxUltimateEnergy)
	FGameplayAttributeData MaxUltimateEnergy;
	ATTRIBUTE_ACCESSORS(USTTCharacterAttributeSet, MaxUltimateEnergy)
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_UltimateEnergy)
	FGameplayAttributeData UltimateEnergy;
	ATTRIBUTE_ACCESSORS(USTTCharacterAttributeSet, UltimateEnergy)


protected:

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	//Rep_Notifies
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_Attack(const FGameplayAttributeData& OldAttack);
	UFUNCTION()
	virtual void OnRep_Defence(const FGameplayAttributeData& OldDefence);
	UFUNCTION()
	virtual void OnRep_EnergyRegen(const FGameplayAttributeData& OldEnergyRegen);
	UFUNCTION()
	virtual void OnRep_CritRate(const FGameplayAttributeData& OldCritRate);
	UFUNCTION()
	virtual void OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage);
	UFUNCTION()
	virtual void OnRep_MaxUltimateEnergy(const FGameplayAttributeData& OldMaxUltimateEnergy);
	UFUNCTION()
	virtual void OnRep_UltimateEnergy(const FGameplayAttributeData& OldUltimateEnergy);
};
