// Fill out your copyright notice in the Description page of Project Settings.


#include "UserController.h"

#include "InteractiveToolManager.h"
#include "Camera/PlayerCameraManager.h"


AUserController::AUserController()
{
	// Shows the mouse cursor && Handle it should use. 
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;
}

void AUserController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AUserController::EdgeScrolling()
{
	// Gets the Viewport Size 
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Gets the Mouse Position
	GetMousePosition(MousePosition.X, MousePosition.Y);

	// Check if the cursor is within the viewport bounds
	bool bCursorOnScreen = MousePosition.X >= 0.0f && MousePosition.X <= static_cast<float>(ViewportSizeX)
		&& MousePosition.Y >= 0.0f && MousePosition.Y <= static_cast<float>(ViewportSizeY);

	bCheckCursor = bCursorOnScreen;

	// Actions to take is the cursor is on the screen
	if (bCursorOnScreen)
	{
		FString MousePosString = FString::Printf(
			TEXT("Mouse Position: X=%.2f, Y=%.2f"), MousePosition.X, MousePosition.Y);
		// Draw the string on the screen
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::White, MousePosString);


		// GONNA NEED TO DO A CHECK TO SEE IF WE ARE HOVERING OVER A BUTTON LATER

		if (MousePosition.X < 30)
		{
			// Moves the camera to the left 
			MoveCamera(FVector(-1.0f, 0.0f, 0.0f));
		}
		else if (MousePosition.X > 1100)
		{
			MoveCamera(FVector(1.0f, 0.f, 0.f));
		}

		// Move Forward
		if (MousePosition.Y < 20)
		{
			MoveCamera(FVector(0.0f, -1.0f, 0.0f));
		}
		else if (MousePosition.Y > 990)
		{
			MoveCamera(FVector(0.0f, 1.0f, 0.0f));
		}
	}
}

void AUserController::MoveCamera(const FVector& Direction)
{
	// Returns the current view target 
	APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(GetViewTarget());
	
	if (AActor* ViewTarget = GetViewTarget())
	{
		// Log information about the CameraManager
		UE_LOG(LogTemp, Warning, TEXT("ViewTarget found!"));

		const float CameraSpeed = 500.f;
		// Get the current view target location
		FVector NewCameraLocation = ViewTarget->GetActorLocation() + Direction * CameraSpeed * GetWorld()->
			GetDeltaSeconds();
		
		// Set the new view target location
		ViewTarget->SetActorLocation(NewCameraLocation);
	}
}

void AUserController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	EdgeScrolling();

}

void AUserController::BeginPlay()
{
	Super::BeginPlay();
}

void AUserController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
