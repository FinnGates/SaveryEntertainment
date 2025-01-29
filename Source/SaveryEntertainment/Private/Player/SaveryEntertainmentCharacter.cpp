// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/SaveryEntertainmentCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Game/SEGameState.h"
#include "Player/SEGravityController.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASaveryEntertainmentCharacter

ASaveryEntertainmentCharacter::ASaveryEntertainmentCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ASaveryEntertainmentCharacter::BeginPlay()
{
	Super::BeginPlay();

	SEGameState = GetWorld()->GetGameState<ASEGameState>();

	SEGravityController = GetController<ASEGravityController>();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASaveryEntertainmentCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ASaveryEntertainmentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Next Colour
		EnhancedInputComponent->BindAction(NextColourAction, ETriggerEvent::Started, this, &ASaveryEntertainmentCharacter::NextColour);

		// Next Colour
		EnhancedInputComponent->BindAction(PreviousColourAction, ETriggerEvent::Started, this, &ASaveryEntertainmentCharacter::PreviousColour);

		// Gravity Up
		EnhancedInputComponent->BindAction(GravityUpAction, ETriggerEvent::Started, this, &ASaveryEntertainmentCharacter::GravityUp);
		
		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ASaveryEntertainmentCharacter::Interact);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASaveryEntertainmentCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASaveryEntertainmentCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASaveryEntertainmentCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FVector GravityDirection = GetCharacterMovement()->GetGravityDirection();
		// find out which way is forward
		const FRotator Rotation = SEGravityController->GetGravityRelativeRotation(SEGravityController->GetControlRotation(), GravityDirection) ;
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FRotator RollYawRotation(0, Rotation.Yaw, Rotation.Roll);
		
		
		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(SEGravityController->GetGravityWorldRotation(YawRotation, GravityDirection)).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(SEGravityController->GetGravityWorldRotation(RollYawRotation, GravityDirection)).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASaveryEntertainmentCharacter::Look(const FInputActionValue& Value)
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

void ASaveryEntertainmentCharacter::NextColour(const FInputActionValue& Value)
{
	SEGameState->ChangeColour(true);
}

void ASaveryEntertainmentCharacter::PreviousColour(const FInputActionValue& Value)
{
	SEGameState->ChangeColour(false);
}

void ASaveryEntertainmentCharacter::GravityUp(const FInputActionValue& Value)
{
	if (GetCharacterMovement()->GetGravityDirection() != FVector::DownVector)
	{
		GetCharacterMovement()->SetGravityDirection(FVector::DownVector);
	}
	else
	{
		GetCharacterMovement()->SetGravityDirection(FVector::UpVector);
	}
}

void ASaveryEntertainmentCharacter::Interact(const FInputActionValue& Value)
{
	if (InteractDelegate.IsBound())
	{
		InteractDelegate.Execute();
	}
}