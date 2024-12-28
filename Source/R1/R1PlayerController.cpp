// Fill out your copyright notice in the Description page of Project Settings.


#include "R1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"

AR1PlayerController::AR1PlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void AR1PlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem != nullptr)
	{
		SubSystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AR1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &AR1PlayerController::Input_Test);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AR1PlayerController::Input_Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AR1PlayerController::Input_Turn);
	}
}

void AR1PlayerController::Input_Test(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Cyan, TEXT("TEST"));
}

void AR1PlayerController::Input_Move(const FInputActionValue& InputValue)
{
	auto MovementVector = InputValue.Get<FVector2D>();

	if (MovementVector.X != 0)
	{
		//FVector Direction = FVector::ForwardVector * MovementVector.X;
		//GetPawn()->AddActorWorldOffset(Direction * 50.0f);
	
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0,Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.X);

	}

	if (MovementVector.Y != 0)
	{
		//FVector Direction = FVector::RightVector * MovementVector.Y;
		//GetPawn()->AddActorWorldOffset(Direction * 50.0f);

		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.Y);
	}
}

void AR1PlayerController::Input_Turn(const FInputActionValue& InputValue)
{
	float Val = InputValue.Get<float>();
	AddYawInput(Val);
}
