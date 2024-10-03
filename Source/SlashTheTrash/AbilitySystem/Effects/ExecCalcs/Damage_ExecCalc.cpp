// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/ExecCalcs/Damage_ExecCalc.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSet/STTCharacterAttributeSet.h"

struct STTDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defence);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritRate);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingDamage);
	
	STTDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(USTTCharacterAttributeSet, Attack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USTTCharacterAttributeSet, Defence, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USTTCharacterAttributeSet, CritRate, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USTTCharacterAttributeSet, CritDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USTTCharacterAttributeSet, IncomingDamage, Target, false);
	}
};

static const STTDamageStatics& DamageStatics()
{
	static STTDamageStatics DamageStatics;
	return DamageStatics;
}

UDamage_ExecCalc::UDamage_ExecCalc()
{
	RelevantAttributesToCapture.Add(DamageStatics().AttackDef);
	RelevantAttributesToCapture.Add(DamageStatics().DefenceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritRateDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().IncomingDamageDef);
}

void UDamage_ExecCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceOwner = SourceASC ? SourceASC->GetOwnerActor() : nullptr;
	const AActor* TargetOwner = TargetASC ? TargetASC->GetOwnerActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Attack = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackDef, EvaluationParameters, Attack);
	Attack = FMath::Max(0.f, Attack);
	
	float CritRate = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritRateDef, EvaluationParameters, CritRate);
	CritRate = FMath::Clamp(CritRate,0.f, 1.f);

	float CritDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritDamageDef, EvaluationParameters, CritDamage);
	CritDamage = FMath::Max(1.f, CritDamage);

	float Defence = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DefenceDef, EvaluationParameters, Defence);
	Defence = FMath::Max(0.f, Defence);

	float IncomingDamage = Attack;
	
	const float RangeCritRateValue = FMath::RandRange(0.f,1.f);
	bool bCrit =  RangeCritRateValue <= CritRate && CritRate > 0;

	if(IncomingDamage >= Defence)
	{
		IncomingDamage = 2 * IncomingDamage - Defence;
	}
	else
	{
		IncomingDamage = IncomingDamage * IncomingDamage / Defence;
	}
	
	IncomingDamage *= bCrit ? CritDamage : 1.f;
	
	const FGameplayModifierEvaluatedData EvaluatedData(DamageStatics().IncomingDamageProperty, EGameplayModOp::Additive, IncomingDamage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
