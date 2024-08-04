// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AttackAnimNotify.h"
#include "AbilitySystemBlueprintLibrary.h"


void UAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                               const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AActor* Owner = MeshComp->GetOwner<AActor>();

	if(IsValid(Owner))
	{
		FGameplayEventData Payload;
		Payload.Instigator = Owner;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, AttackEventTag, Payload);
	}
}
