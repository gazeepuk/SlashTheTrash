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

void USTTCharacterAttributeSet::OnRep_MaxUltimateEnergy(const FGameplayAttributeData& OldMaxUltimateEnergy)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, MaxUltimateEnergy, OldMaxUltimateEnergy);
}

void USTTCharacterAttributeSet::OnRep_UltimateEnergy(const FGameplayAttributeData& OldUltimateEnergy)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(USTTCharacterAttributeSet, UltimateEnergy, OldUltimateEnergy);
}

#pragma endregion

void USTTCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		//Clamp new health
		SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	}
	if(Data.EvaluatedData.Attribute == GetUltimateEnergyAttribute())
	{
		const float EnergyValueToRestore = Data.EvaluatedData.Magnitude;
		//Clamp new value
		SetUltimateEnergy(FMath::Clamp(EnergyValueToRestore, 0, GetMaxUltimateEnergy()));
	}
	if(Data.EvaluatedData.Attribute == GetIncomingEnergyAttribute())
	{
		//Get incoming energy value 
		const float LocalIncomingEnergy = GetIncomingEnergy();
		SetIncomingEnergy(0);

		//Apply RestoreEnergy multiplier
		const float LocalEnergyRegen = FMath::Max(0, GetEnergyRegen());
		float EnergyToRestore = LocalIncomingEnergy * LocalEnergyRegen;
		
		//Set new UltimateEnergy value with clamping
		SetUltimateEnergy(FMath::Clamp(GetUltimateEnergy() + EnergyToRestore, 0.f, GetMaxUltimateEnergy()));
	}
	if(Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		//Get incoming damage
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0);

		//Calculate damage to apply
		float DamageToApply = 0.f;
		if(LocalIncomingDamage >= GetDefence())
		{
			DamageToApply = LocalIncomingDamage * 2.f - GetDefence();
		}
		else
		{
			DamageToApply = LocalIncomingDamage * LocalIncomingDamage / GetDefence();
		}

		//Apply new health with clamping
		const float NewHealth = GetHealth() - DamageToApply;
		SetHealth(FMath::Clamp(NewHealth, 0 ,GetMaxHealth()));
	}

}
#pragma endregion
