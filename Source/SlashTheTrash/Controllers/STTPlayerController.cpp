// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/STTPlayerController.h"

#include "EnhancedInputSubsystems.h"

ASTTPlayerController::ASTTPlayerController()
{
	bReplicates = true;
}

void ASTTPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(STTMappingContext);

	bShowMouseCursor = false;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	InputMode.SetHideCursorDuringCapture(true);
	SetInputMode(InputMode);
}
