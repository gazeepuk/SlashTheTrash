// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CharacterOpenWorldHUD.h"

#include "Kismet/GameplayStatics.h"
#include "PlayerStates/STTPlayerStateBase.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "UI/Widgets/OpenWorld/OverlayOpenWorldWidget.h"


UWidgetControllerParams* ACharacterOpenWorldHUD::GetWidgetControllerParams() const
{
	return GetWidgetControllerParamsByClass<UWidgetControllerParams>();
}

template <class T>
UWidgetControllerParams* ACharacterOpenWorldHUD::GetWidgetControllerParamsByClass() const
{
	APlayerController* PC = GetOwningPlayerController();
	APlayerState* State = UGameplayStatics::GetPlayerState(this, 0);
	ASTTPlayerStateBase* PS = State ? Cast<ASTTPlayerStateBase>(State) : nullptr;
	UAbilitySystemComponent* ASC = PS ? PS->GetAbilitySystemComponent() : nullptr;
	UAttributeSet* AS = PS ? PS->GetAttributeSet() : nullptr;

	UWidgetControllerParams* WidgetControllerParams = NewObject<T>();
	WidgetControllerParams->InitParams(ASC,AS,PC,PS);
	return WidgetControllerParams;
}

void ACharacterOpenWorldHUD::SetOverlayOpenWorldWidgetFromHUD()
{
	SetOverlayOpenWorldWidget(GetWidgetControllerParamsByClass<UCharacterWidgetControllerParams>());
}

void ACharacterOpenWorldHUD::SetOverlayOpenWorldWidget(UWidgetControllerParams* InWidgetParams)
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

UOverlayOpenWorldWidgetController* ACharacterOpenWorldHUD::GetOverlayOpenWorldWidgetController(UWidgetControllerParams* InParams)
{
	//Create WidgetController if it doesn't exist
	if(!OverlayOpenWorldWidgetController)
	{
		if(IsValid(OverlayOpenWorldWidgetControllerClass))
		{
			OverlayOpenWorldWidgetController = NewObject<UOverlayOpenWorldWidgetController>(this, OverlayOpenWorldWidgetControllerClass);
			OverlayOpenWorldWidgetController->SetWidgetControllerParams(InParams);
			OverlayOpenWorldWidgetController->BindCallbacksToDependencies();
			return OverlayOpenWorldWidgetController;
		}
		return nullptr;
	}
	return OverlayOpenWorldWidgetController;
}
