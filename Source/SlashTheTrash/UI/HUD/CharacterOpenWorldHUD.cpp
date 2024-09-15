// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CharacterOpenWorldHUD.h"

#include "PlayerStates/STTPlayerStateBase.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "UI/Widgets/OpenWorld/OverlayOpenWorldWidget.h"


FWidgetControllerParams ACharacterOpenWorldHUD::GetWidgetControllerParams() const
{
	
	APlayerController* PC = GetOwningPlayerController();
	ASTTPlayerStateBase* PS = PC ? PC->GetPlayerState<ASTTPlayerStateBase>() : nullptr;
	UAbilitySystemComponent* ASC = PS ? PS->GetAbilitySystemComponent() : nullptr;
	UAttributeSet* AS = PC ? PS->GetAttributeSet() : nullptr;
	
	return FWidgetControllerParams(ASC,AS,PC,PS);
}

void ACharacterOpenWorldHUD::SetOverlayOpenWorldWidgetFromHUD()
{
	SetOverlayOpenWorldWidget(GetWidgetControllerParams());
}

void ACharacterOpenWorldHUD::SetOverlayOpenWorldWidget(const FWidgetControllerParams& InWidgetParams)
{
	//Create widget
	if(IsValid(OverlayOpenWorldWidgetClass))
	{
		OverlayOpenWorldWidget = CreateWidget<UOverlayOpenWorldWidget>(GetOwningPlayerController(), OverlayOpenWorldWidgetClass);
	}

	//Setup widget and add to viewport
	if(OverlayOpenWorldWidget)
	{
		OverlayOpenWorldWidget->SetWidgetController(GetOverlayOpenWorldWidgetController(InWidgetParams));
		OverlayOpenWorldWidget->AddToViewport();
	}
}

UOverlayOpenWorldWidgetController* ACharacterOpenWorldHUD::GetOverlayOpenWorldWidgetController(const FWidgetControllerParams& InParams)
{
	//Create WidgetController if it doesn't exist
	if(!OverlayOpenWorldWidgetController)
	{
		if(IsValid(OverlayOpenWorldWidgetControllerClass))
		{
			OverlayOpenWorldWidgetController = NewObject<UOverlayOpenWorldWidgetController>(this, OverlayOpenWorldWidgetControllerClass);
			OverlayOpenWorldWidgetController->SetWidgetControllerParams(InParams);
			return OverlayOpenWorldWidgetController;
		}
		return nullptr;
	}
	return OverlayOpenWorldWidgetController;
}
