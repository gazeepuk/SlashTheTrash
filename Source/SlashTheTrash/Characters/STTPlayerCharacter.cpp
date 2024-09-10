// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/STTPlayerCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/Abilities/STTGameplayAbilityBase.h"
#include "AbilitySystem/Abilities/ComboAttacks/STTComboAttackBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerStates/STTPlayerStateBase.h"

static TAutoConsoleVariable<int32> CVarShowDebugSTTCharacter(
	TEXT("ShowDebugSTTCharacter"),
	0,
	TEXT("Show character debug")
	TEXT(" 0: off/n")
	TEXT(" 1: on/n"),
	ECVF_Cheat
);

UAbilitySystemComponent* ASTTPlayerCharacter::GetAbilitySystemComponent() const
{
	ASTTPlayerStateBase* STTPlayerState = GetPlayerState<ASTTPlayerStateBase>();
	return STTPlayerState ? STTPlayerState->GetAbilitySystemComponent() : nullptr;
}

UAttributeSet* ASTTPlayerCharacter::GetAttributeSet() const
{
	ASTTPlayerStateBase* STTPlayerState = GetPlayerState<ASTTPlayerStateBase>();
	return STTPlayerState ? STTPlayerState->GetAttributeSet() : nullptr;
}

ASTTPlayerCharacter::ASTTPlayerCharacter()
{
	CameraBoomComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoomComponent->SetupAttachment(GetRootComponent());
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoomComponent, USpringArmComponent::SocketName);

	CameraBoomComponent->bUsePawnControlRotation = true;
	CameraComponent->bUsePawnControlRotation = false;
}

void ASTTPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

// Called to bind functionality to input
void ASTTPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind InputActions
	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Bind Attacks
		if(IsValid(NormalAttackInputAction))
		{
			EnhancedInputComponent->BindAction(NormalAttackInputAction, ETriggerEvent::Started, this, &ThisClass::UseNormalAttack);
		}
		if(IsValid(HardAttackInputAction))
		{
			EnhancedInputComponent->BindAction(HardAttackInputAction, ETriggerEvent::Started, this, &ThisClass::UseHardAttack);
		}
		if(IsValid(MoveAction))
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		}
		if(IsValid(LookAction))
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
		}
		if(IsValid(JumpAction))
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::StartJumpInput);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumpInput);
		}
		
	}
}

void ASTTPlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASTTPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASTTPlayerCharacter::StartJumpInput(const FInputActionValue& Value)
{
	if(IsValid(GetAbilitySystemComponent()) && JumpEventTag.IsValid())
	{
		FGameplayEventData Payload;
		Payload.Instigator = this;
		Payload.EventTag = JumpEventTag;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, JumpEventTag, Payload);
	}
}

void ASTTPlayerCharacter::StopJumpInput(const FInputActionValue& Value)
{
	StopJumping();
}

void ASTTPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	//Init ActorInfo for the Server
	InitAbilitySystemComponent();
	GiveDefaultAbilities();
}

void ASTTPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	//Init ActorInfo for the Client
	InitAbilitySystemComponent();
}

void ASTTPlayerCharacter::UseNormalAttack(const FInputActionValue& Value)
{
	const bool bDebug = CVarShowDebugSTTCharacter.GetValueOnGameThread() != 0;

	TSubclassOf<USTTGameplayAbilityBase> NextAbilityClass;

	//Checking for last attack
	if(IsValid(LastComboAttackClass))
	{
		//Get next Normal attack from the previous attack
		NextAbilityClass = LastComboAttackClass.GetDefaultObject()->GetComboAttackStaticInfo().NextNormalAttackClass;
		// If attack class is invalid, get default Normal attack class
		if(!IsValid(NextAbilityClass))
		{
			NextAbilityClass = DefaultNormalAttackClass;
			if(bDebug)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s next normal attack is invalid. Uses default ability: %s"), *LastComboAttackClass->GetName(), NextAbilityClass ? *NextAbilityClass->GetName() : TEXT("NULL")));
			}
		}
	}
	//If last attack is invalid, get default Normal attack class
	else
	{
		NextAbilityClass = DefaultNormalAttackClass;
		if(bDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Last combo attack is invalid. Uses default ability: %s"), NextAbilityClass ? *NextAbilityClass->GetName() : TEXT("NULL")));
		}
	}

	//Try to activate ability
	if(IsValid(NextAbilityClass) && IsValid(GetAbilitySystemComponent()))
	{
		const bool bActivated = GetAbilitySystemComponent()->TryActivateAbilityByClass(NextAbilityClass);
		if(bDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Activated ability %s %s"), *NextAbilityClass->GetName(), bActivated ? TEXT("successfuly") : TEXT("unseccessfuly")));
		}
	}
	else if(bDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Can't activate ability. Ability class: %s. AbilitySystemComponent: %s"), NextAbilityClass ? *NextAbilityClass->GetName() : TEXT("NULL"), AbilitySystemComponent ? *AbilitySystemComponent.GetName() : TEXT("NULL")));
	}
}

void ASTTPlayerCharacter::UseHardAttack(const FInputActionValue& Value)
{
	const bool bDebug = CVarShowDebugSTTCharacter.GetValueOnGameThread() != 0;

	TSubclassOf<USTTGameplayAbilityBase> NextAbilityClass;

	//Checking for last attack
	if(IsValid(LastComboAttackClass))
	{
		//Get next Hard attack from the previous attack
		NextAbilityClass = LastComboAttackClass.GetDefaultObject()->GetComboAttackStaticInfo().NextHardAttackClass;
		// If attack class is invalid, get default Hard attack class
		if(!IsValid(NextAbilityClass))
		{
			NextAbilityClass = DefaultHardAttackClass;
			if(bDebug)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s next Hard attack is invalid. Uses default ability: %s"), *LastComboAttackClass->GetName(), NextAbilityClass ? *NextAbilityClass->GetName() : TEXT("NULL")));
			}
		}
	}
	//If last attack is invalid, get default Hard attack class
	else
	{
		NextAbilityClass = DefaultHardAttackClass;
		if(bDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Last combo attack is invalid. Uses default ability: %s"), NextAbilityClass ? *NextAbilityClass->GetName() : TEXT("NULL")));
		}
	}

	//Try to activate ability
	if(IsValid(NextAbilityClass) && IsValid(GetAbilitySystemComponent()))
	{
		const bool bActivated = GetAbilitySystemComponent()->TryActivateAbilityByClass(NextAbilityClass);
		if(bDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Activated ability %s %s"), *NextAbilityClass->GetName(), bActivated ? TEXT("successfuly") : TEXT("unseccessfuly")));
		}
	}
	else if(bDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Can't activate ability. Ability class: %s. AbilitySystemComponent: %s"), NextAbilityClass ? *NextAbilityClass->GetName() : TEXT("NULL"), AbilitySystemComponent ? *AbilitySystemComponent.GetName() : TEXT("NULL")));
	}
}

void ASTTPlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if(GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->RemoveActiveEffectsWithTags(JumpEffectTag);
	}
}


void ASTTPlayerCharacter::OnAbilityCommited(UGameplayAbility* GameplayAbility)
{
	if(IsValid(GameplayAbility) && GameplayAbility->IsA(USTTComboAttackBase::StaticClass()))
	{
		LastComboAttackClass = GameplayAbility->GetClass();
	}
}

void ASTTPlayerCharacter::InitAbilitySystemComponent()
{
	Super::InitAbilitySystemComponent();

	check(GetAbilitySystemComponent());

	ASTTPlayerStateBase* STTPlayerState = GetPlayerState<ASTTPlayerStateBase>();
	checkf(STTPlayerState, TEXT("STTPlayerState is nullptr"))

	GetAbilitySystemComponent()->InitAbilityActorInfo(STTPlayerState, this);
	ApplyDefaultAttributes();

	GetAbilitySystemComponent()->AbilityCommittedCallbacks.Remove(OnCommitAbilityHandle);
	OnCommitAbilityHandle = GetAbilitySystemComponent()->AbilityCommittedCallbacks.AddUObject(this, &ASTTPlayerCharacter::OnAbilityCommited);
}


void ASTTPlayerCharacter::ResetLastComboAttackClass()
{
	LastComboAttackClass = nullptr;
}
