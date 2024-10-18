// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ShowWeaponAnimNotify.h"

#include "Characters/STTCharacterBase.h"

void UShowWeaponAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(ASTTCharacterBase* STTCharacter = MeshComp->GetOwner<ASTTCharacterBase>())
	{
		STTCharacter->SetWeaponVisibility(bShowWeapon);
	}
}
