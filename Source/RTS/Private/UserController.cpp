// Fill out your copyright notice in the Description page of Project Settings.


#include "UserController.h"

#include "InteractiveToolManager.h"
#include "UserCharacter.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/SpringArmComponent.h"


AUserController::AUserController()
{
	// Shows the mouse cursor && Handle it should use. 
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;

	// Used to check if we are drawing or selecting units.
	bIsSelecting = false;
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
			MoveCamera(FVector(0.0f, -1.0f, 0.0f));
			bCursorMove = true;
		}
		else if (MousePosition.X > 1900)
		{
			// Moves Camera to the right
			MoveCamera(FVector(0.0f, 1.f, 0.f));
			bCursorMove = true;
		}
		else
		{
			bCursorMove = false;
		}

		// Move Forward
		if (MousePosition.Y < 20)
		{
			MoveCamera(FVector(1.0f, 0.0f, 0.0f));
			bCursorMove = true;
		}
		else if (MousePosition.Y > 990)
		{
			MoveCamera(FVector(-1.0f, 0.0f, 0.0f));
			bCursorMove = true;
		}
		else
		{
			bCursorMove = false;
		}
	}
}

void AUserController::EdgeScrolling_WASD_Up(float Value)
{
	if (Value)
	{
		MoveCamera(FVector(2.0f, 0.0f, 0.0f));
	}
}

void AUserController::EdgeScrolling_WASD_Down(float Value)
{
	if (Value)
	{
		MoveCamera(FVector(-2.0f, 0.0f, 0.0f));
	}
}

void AUserController::EdgeScrolling_WASD_Right(float Value)
{
	if (Value)
	{
		MoveCamera(FVector(0.0f, 2.0f, 0.0f));
	}
}

void AUserController::EdgeScrolling_WASD_Left(float Value)
{
	if (Value)
	{
		MoveCamera(FVector(0.0f, -2.0f, 0.0f));
	}
}

void AUserController::MoveCamera(const FVector& Direction)
{
	// Returns the current view target 
	APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(GetViewTarget());

	if (AActor* ViewTarget = GetViewTarget())
	{
		// Log information about the CameraManager
		//UE_LOG(LogTemp, Warning, TEXT("ViewTarget found!"));

		if (bCursorMove)
		{
			const float CameraSpeed = 500;
			// Get the current view target location
			FVector NewCameraLocation = ViewTarget->GetActorLocation() + Direction * CameraSpeed * GetWorld()->
				GetDeltaSeconds();

			// Set the new view target location
			ViewTarget->SetActorLocation(NewCameraLocation);
		}
		else
		{
			const float CameraSpeed = 1000;
			// Get the current view target location
			FVector NewCameraLocation = ViewTarget->GetActorLocation() + Direction * CameraSpeed * GetWorld()->
				GetDeltaSeconds();

			// Set the new view target location
			ViewTarget->SetActorLocation(NewCameraLocation);
		}
	}
}

void AUserController::ZoomIn(float Value)
{

	
	
	// Get the current arm length
	//float CurrentArmLength = UserCharacter->CameraBoom->TargetArmLength;

	/*FString ValueOfZoom = FString::Printf(
	TEXT("Zoom Value: X=%.2f"), Value);

	// Draw the string on the screen
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::White, ValueOfZoom);
	

	//AUserCharacter* UserCharacter;
	if (UserCharacter)
	{
		USpringArmComponent* CameraBoom = UserCharacter->GetCameraBoom();
		if (CameraBoom)
		{
			// Get the current TargetArmLength
			float TargetArmLength = CameraBoom->TargetArmLength;

			// Convert the TargetArmLength to a string
			FString ArmLengthString = FString::Printf(TEXT("TargetArmLength: %f"), TargetArmLength);

			// Display the TargetArmLength on the screen
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, ArmLengthString);
		}
		else
		{
			// Handle the case where GetCameraBoom() returns nullptr
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CameraBoom is nullptr."));
		}
	}
	else
	{
		// Handle the case where GetUserCharacter() returns nullptr
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("UserCharacter is nullptr."));
	}
	*/
	
}

void AUserController::ZoomOut(float Value)
{
	/*GetUser()->GetCameraBoom()->TargetArmLength -= Value;

if (GetUser()->GetCameraBoom()->TargetArmLength < MinZoom)
{
	GetUser()->GetCameraBoom()->TargetArmLength = MinZoom;
}*/
}

void AUserController::Left_Camera_Rotation()
{
	
}

void AUserController::Right_Camera_Rotation()
{
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

	// Controls The Camera Movement 
	InputComponent->BindAxis("Up", this, &AUserController::EdgeScrolling_WASD_Up);
	InputComponent->BindAxis("Down", this, &AUserController::EdgeScrolling_WASD_Down);
	InputComponent->BindAxis("Right", this, &AUserController::EdgeScrolling_WASD_Right);
	InputComponent->BindAxis("Left", this, &AUserController::EdgeScrolling_WASD_Left);

	// Controls the Camera Zoom Capabilities
	InputComponent->BindAxis("ZoomIn", this, &AUserController::ZoomIn);
	InputComponent->BindAxis("ZoomOut", this, &AUserController::ZoomOut);
	
	// Rotates the Camera 
	InputComponent->BindAxis("ZoomIn", this, &AUserController::ZoomIn);
	InputComponent->BindAxis("ZoomOut", this, &AUserController::ZoomOut);

	// Draw Box and select units 
	InputComponent->BindAction("BoxSelection", IE_Pressed, this, &AUserController::StartBoxSelection);
	InputComponent->BindAction("UpdateBoxSelection", IE_Released, this, &AUserController::EndBoxSelection);
	//InputComponent->BindAction("UpdateBoxSelection", IE_Axis, this, &AUserController::UpdateBoxSelection);
	
}

void AUserController::StartBoxSelection()
{
	
	
	// We Use this function to select an item or unit.
	// ONLY Draw a square if the coordinates start moving. 

	// Get initial Mouse Coordinates
	// Then do Logic
	// Unless, if the mouse coordinates change while pressing down the input
	// So do an if statement to check if the mouse if moving.


	if(GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		UWorld* World = GetWorld();
		
		//DrawDebugBox(World, FVector(MousePosition.X), FVector(MousePosition.Y), FColor::Blue);
		UE_LOG(LogTemp, Warning, TEXT("StartBoxSelection called"));
	}
	
	bIsSelecting = true;
	// Boolean Function
}

void AUserController::UpdateBoxSelection()
{
	if (bIsSelecting)
	{
		GetMousePosition(CurrentMousePosition.X, CurrentMousePosition.Y);

		// Calculate the size of the selection box
		FVector2d BoxSize = CurrentMousePosition - MousePosition;

		UE_LOG(LogTemp, Warning, TEXT("StartBoxSelection Updated"));
	}
}

void AUserController::EndBoxSelection()
{
	bIsSelecting = false;
	UE_LOG(LogTemp, Warning, TEXT("StartBoxSelection ended"));
}



/*// Convert BoxSize to FString
	FString BoxSizeString = FString::Printf(TEXT("Box Size: X=%.2f, Y=%.2f"), BoxSize.X, BoxSize.Y);
	
	// Print the FString to the GEngine output log
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, BoxSizeString);*/