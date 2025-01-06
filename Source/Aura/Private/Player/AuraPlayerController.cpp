// Copyright Pascal Lefev

#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(AuraInputContext);

	const auto Subsystem{ ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()) };
	check(Subsystem);
	Subsystem->AddMappingContext(AuraInputContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent{ CastChecked<UEnhancedInputComponent>(InputComponent) };

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& Value)
{
	const auto InputAxisVector{ Value.Get<FVector2D>() };
	const auto Rotation{ GetControlRotation() };
	const auto YawRotation{ FRotator{ 0.f, Rotation.Yaw, 0.f } };
	
	const auto ForwardDirection{ FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) };
	const auto RightDirection{ FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) };

	if (const auto ControlPawn{ GetPawn<APawn>() })
	{
		ControlPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
