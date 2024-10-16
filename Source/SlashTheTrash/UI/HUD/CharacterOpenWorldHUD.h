// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/STTHUDBase.h"
#include "UI/WidgetControllers/WidgetControllerBase.h"
#include "CharacterOpenWorldHUD.generated.h"

class USTTUserWidgetBase;
class UOverlayOpenWorldWidgetController;
class UOverlayOpenWorldWidget;
/**
 * 
 */
UCLASS()
class SLASHTHETRASH_API ACharacterOpenWorldHUD : public ASTTHUDBase
{
	GENERATED_BODY()
public:
	//Get WidgetController from HUD
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UWidgetControllerParams* GetWidgetControllerParams() const;

	template<class T>
	UWidgetControllerParams* GetWidgetControllerParamsByClass() const;
	

	//Set OverlayWidget
	UFUNCTION(BlueprintCallable)
	void SetOverlayOpenWorldWidgetFromHUD();
	UFUNCTION(BlueprintCallable)
	void SetOverlayOpenWorldWidget(UWidgetControllerParams* InWidgetParams);

	//Getter OverlayOpenWorldController 
	UFUNCTION(BlueprintCallable)
	UOverlayOpenWorldWidgetController* GetOverlayOpenWorldWidgetController(UWidgetControllerParams* InParams);
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USTTUserWidgetBase> OverlayOpenWorldWidget;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UOverlayOpenWorldWidgetController> OverlayOpenWorldWidgetController;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOverlayOpenWorldWidget> OverlayOpenWorldWidgetClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOverlayOpenWorldWidgetController> OverlayOpenWorldWidgetControllerClass;
};
