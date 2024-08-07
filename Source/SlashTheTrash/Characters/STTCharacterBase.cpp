// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/STTCharacterBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/STTAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/STTGameplayAbilityBase.h"
#include "AbilitySystem/Abilities/ComboAttacks/STTComboAttackBase.h"
#include "AbilitySystem/AttributeSet/STTCharacterAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerState.h"
#include "Data/CharacterDataAsset.h"
#include "Data/CharacterAbilitiesDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

static TAutoConsoleVariable<int32> CVarShowDebugSTTCharacter(
	TEXT("ShowDebugSTTCharacter"),
	0,
	TEXT("Show character debug")
	TEXT(" 0: off/n")
	TEXT(" 1: on/n"),
	ECVF_Cheat
);

// Sets default values
ASTTCharacterBase::ASTTCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Setup Ability System
	AbilitySystemComponent = CreateDefaultSubobject<USTTAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<USTTCharacterAttributeSet>(TEXT("AttributeSet"));

	AbilitySystemComponent->AbilityCommittedCallbacks.AddUObject(this, &ThisClass::OnAbilityCommited);

	CameraBoomComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoomComponent->SetupAttachment(GetRootComponent());
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoomComponent, USpringArmComponent::SocketName);

	CameraBoomComponent->bUsePawnControlRotation = true;
	CameraComponent->bUsePawnControlRotation = false;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	
}

void ASTTCharacterBase::ResetLastComboAttackClass()
{
	LastComboAttackClass = nullptr;
}

// Called when the game starts or when spawned
void ASTTCharacterBase::BeginPlay()
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

void ASTTCharacterBase::OnAbilityCommited(UGameplayAbility* GameplayAbility)
{
	if(IsValid(GameplayAbility) && GameplayAbility->IsA(USTTComboAttackBase::StaticClass()))
	{
		LastComboAttackClass = GameplayAbility->GetClass();
	}
}

// Called to bind functionality to input
void ASTTCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		}
		
	}
}

void ASTTCharacterBase::Move(const FInputActionValue& Value)
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

void ASTTCharacterBase::Look(const FInputActionValue& Value)
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

void ASTTCharacterBase::StartJumpInput(const FInputActionValue& Value)
{
	FGameplayEventData Payload;
	Payload.EventTag = JumpEventTag;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, JumpEventTag, Payload);
}

void ASTTCharacterBase::StopJumpInput(const FInputActionValue& Value)
{
}

void ASTTCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (AbilitySystemComponent && IsValid(CharacterDataAsset))
	{
		//Apply default effect
		if(IsValid(CharacterDataAsset->DefaultGameplayEffect))
		{
			FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
			FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(CharacterDataAsset->DefaultGameplayEffect,1,ContextHandle);
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}

		//Apply default abilities
		if (IsValid(CharacterDataAsset->CharacterAbilitiesDataAsset))
		{
			for (const TSubclassOf<USTTGameplayAbilityBase>& DefaultAbility : CharacterDataAsset->CharacterAbilitiesDataAsset->GetDefaultAbilities())
			{
				AbilitySystemComponent->K2_GiveAbility(*DefaultAbility);
			}
		}
	}
}

void ASTTCharacterBase::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->RemoveActiveEffectsWithTags(InAirTags);
	}
}

void ASTTCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AbilitySystemComponent->InitAbilityActorInfo(GetPlayerState(), this);
}

void ASTTCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	AbilitySystemComponent->InitAbilityActorInfo(GetPlayerState(), this);
}

UAbilitySystemComponent* ASTTCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void ASTTCharacterBase::GetDamage_Implementation(FGameplayEffectSpec& DamageEffect)
{
	if(IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(DamageEffect);
	}
}

void ASTTCharacterBase::UseNormalAttack(const FInputActionValue& Value)
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
	if(IsValid(NextAbilityClass) && IsValid(AbilitySystemComponent))
	{
		const bool bActivated = AbilitySystemComponent->TryActivateAbilityByClass(NextAbilityClass);
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

void ASTTCharacterBase::UseHardAttack(const FInputActionValue& Value)
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
	if(IsValid(NextAbilityClass) && IsValid(AbilitySystemComponent))
	{
		const bool bActivated = AbilitySystemComponent->TryActivateAbilityByClass(NextAbilityClass);
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


