// Copyright Pascal Lefev

#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

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

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
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

void AAuraPlayerController::CursorTrace()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (!Hit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Hit.GetActor();

	if (LastActor == nullptr)
	{
		if (ThisActor == nullptr) return;
		ThisActor->HighlightActor();
		return;
	}
	
	if (ThisActor == nullptr)
	{
		LastActor->UnHighlightActor();
		return;
	}

	if (LastActor != ThisActor)
	{
		LastActor->UnHighlightActor();
		ThisActor->HighlightActor();
	}
}