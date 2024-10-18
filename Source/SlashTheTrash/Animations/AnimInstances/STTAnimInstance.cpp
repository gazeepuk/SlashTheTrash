// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AnimInstances/STTAnimInstance.h"
#include "Characters/STTCharacterBase.h"
#include "Data/CharacterAnimationsDataAsset.h"
#include "Data/CharacterDataAsset.h"

UCharacterAnimationsDataAsset* USTTAnimInstance::GetAnimationsDataAsset() const
{
	AActor* Owner = GetOwningActor();
	ASTTCharacterBase* STTOwner = Cast<ASTTCharacterBase>(Owner);
	if(STTOwner)
	{
		return STTOwner->CharacterDataAsset ? STTOwner->CharacterDataAsset->CharacterAnimationsDataAsset : nullptr;
	}
	return nullptr;
}

UBlendSpace* USTTAnimInstance::GetMovementBlendSpace() const
{
	return GetAnimationsDataAsset() ? GetAnimationsDataAsset()->MovementBlendSpace : nullptr;
}

UAnimMontage* USTTAnimInstance::GetDamageAnimation() const
{
	return GetAnimationsDataAsset() ? GetAnimationsDataAsset()->GetDamageAnimation : nullptr;
}

UAnimMontage* USTTAnimInstance::DiedAnimation() const
{
	return GetAnimationsDataAsset() ? GetAnimationsDataAsset()->DeathAnimation : nullptr;
}

UAnimSequenceBase* USTTAnimInstance::GetIdleAnimation() const
{
	return GetAnimationsDataAsset() ? GetAnimationsDataAsset()->IdleAnimation : nullptr;
}
