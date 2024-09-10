// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSet/STTCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void USTTCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USTTCharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USTTCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USTTCharacterAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USTTCharacterAttributeSet, Defence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USTTCharacterAttributeSet, EnergyRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USTTCharacterAttributeSet, CritRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USTTCharacterAttributeSet, CritDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USTTCharacterAttributeSet, MaxBattleEnergy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USTTCharacterAttributeSet, BattleEnergy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USTTCharacterAttributeSet, MaxUltimateEnergy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USTTCharacterAttributeSet, UltimateEnergy, COND_None, REPNOTIFY_Always);
	
}

#pragma region OnRep_Notifies
void USTTCharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, MaxHealth, OldMaxHealth);
}

void USTTCharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, Health, OldHealth);
}

void USTTCharacterAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldAttack)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, Attack, OldAttack);
}

void USTTCharacterAttributeSet::OnRep_Defence(const FGameplayAttributeData& OldDefence)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, Defence, OldDefence);
}

void USTTCharacterAttributeSet::OnRep_EnergyRegen(const FGameplayAttributeData& OldEnergyRegen)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, EnergyRegen, OldEnergyRegen);
}

void USTTCharacterAttributeSet::OnRep_CritRate(const FGameplayAttributeData& OldCritRate)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, CritRate, OldCritRate);
}

void USTTCharacterAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, CritDamage, OldCritDamage);
}

void USTTCharacterAttributeSet::OnRep_MaxBattleEnergy(const FGameplayAttributeData& OldMaxBattleEnergy)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, MaxBattleEnergy, OldMaxBattleEnergy);
}

void USTTCharacterAttributeSet::OnRep_BattleEnergy(const FGameplayAttributeData& OldBattleEnergy)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, BattleEnergy, OldBattleEnergy);
}

void USTTCharacterAttributeSet::OnRep_MaxUltimateEnergy(const FGameplayAttributeData& OldMaxUltimateEnergy)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, MaxUltimateEnergy, OldMaxUltimateEnergy);
}

void USTTCharacterAttributeSet::OnRep_UltimateEnergy(const FGameplayAttributeData& OldUltimateEnergy)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, UltimateEnergy, OldUltimateEnergy);
}


void USTTCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	}
	if(Data.EvaluatedData.Attribute == GetUltimateEnergyAttribute())
	{
		//Applying EnergyRegen bonus
		
		float EnergyValueToRestore = Data.EvaluatedData.Magnitude;
		//Undo restoring energy
		float CurrentUltimateEnergy = GetUltimateEnergy();
		SetUltimateEnergy(FMath::Clamp(CurrentUltimateEnergy - EnergyValueToRestore, 0, GetMaxUltimateEnergy()));
		CurrentUltimateEnergy = GetUltimateEnergy();
		//Get EnergyRegen bonus
		float EnergyRegenValue = FMath::Max(1, GetEnergyRegen());

		//Apply bonus to restoring energy
		EnergyValueToRestore *= EnergyRegenValue;

		//Calculate final ultimate energy value 
		float FinalUltimateEnergyValue = CurrentUltimateEnergy + EnergyValueToRestore;
		FinalUltimateEnergyValue = FMath::Clamp(FinalUltimateEnergyValue, 0, GetMaxUltimateEnergy());
		SetUltimateEnergy(FinalUltimateEnergyValue);
	}
}
#pragma endregion
