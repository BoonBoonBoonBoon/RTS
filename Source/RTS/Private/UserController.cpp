// Fill out your copyright notice in the Description page of Project Settings.


#include "UserController.h"

#include "InteractiveToolManager.h"
#include "UserCharacter.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


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
	Update();
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
	//InputComponent->BindAction("UpdateBoxSelection", IE_Held, this, &AUserController::UpdateBoxSelection);
	
}

void AUserController::StartBoxSelection()
{
	// We Use this function to select an item or unit.
	// ONLY Draw a square if the coordinates start moving. 

	// Get initial Mouse Coordinates
	// Then do Logic
	// Unless, if the mouse coordinates change while pressing down the input
	// So do an if statement to check if the mouse if moving.
	
	// When just clicking, Shoot a line trace from the camera to the object you want to pick, This will work as single use selection then use if statement for multi.........
	if (GetMousePosition(InitialMousePosition.X, InitialMousePosition.Y))
	{
		FString MousePosString = FString::Printf(
			TEXT("SingleSelectionMouse Position: X=%.2f, Y=%.2f"), InitialMousePosition.X, InitialMousePosition.Y);

		UE_LOG(LogTemp, Warning, TEXT("%s"), *MousePosString);

		bIsSelecting = true;
	}
}

void AUserController::Update()
{
	if(bIsSelecting)
	{
		// Checks if the mouse has been moved
		if(HasCursorMoved())
		{
			UE_LOG(LogTemp, Warning, TEXT("Moved"));
			 // if mouse has been moved updated the coordinates of the square.
			Draw2DSSquare(InitialMousePosition,NULL);
		} else
		{
			//SelectUnitCode
		}
	}
}

bool AUserController::HasCursorMoved()
{
	FVector2D CurrentCursor;
	GetMousePosition(CurrentCursor.X, CurrentCursor.Y);

	// Compares The current cursor location with the first cursor location
	if(CurrentCursor != InitialMousePosition)
	{
		return true;
		//return CurrentCursor != InitialMousePosition;
	}
	
	return false;
}

void AUserController::Draw2DSSquare(const FVector2D& Center, float Size)
{
	// The half size of the square
	float HalfSize = Size / 2.0f;

	// Center CornerPoint where the point will originate
	FVector2D CenterPoint = InitialMousePosition;
	
    // Corner points of the square
    FVector2D TopLeft = Center + FVector2D(-HalfSize, -HalfSize);
    FVector2D TopRight = Center + FVector2D(HalfSize, -HalfSize);
    FVector2D BottomLeft = Center + FVector2D(-HalfSize, HalfSize);
    FVector2D BottomRight = Center + FVector2D(HalfSize, HalfSize);

    // Line trace from TopLeft to TopRight
    /*
    FHitResult HitResultTop;

	
	LineTraceSingleByChannel(
        HitResultTop,
        FVector(TopLeft, 0.0f),
        FVector(TopRight, 0.0f),
        ECC_Visibility
    );

    // Line trace from TopRight to BottomRight
    FHitResult HitResultRight;
    LineTraceSingleByChannel(
        HitResultRight,
        FVector(TopRight, 0.0f),
        FVector(BottomRight, 0.0f),
        ECC_Visibility
    );

    // Line trace from BottomRight to BottomLeft
    FHitResult HitResultBottom;
    LineTraceSingleByChannel(
        HitResultBottom,
        FVector(BottomRight, 0.0f),
        FVector(BottomLeft, 0.0f),
        ECC_Visibility
    );

    // Line trace from BottomLeft to TopLeft
    FHitResult HitResultLeft;
    LineTraceSingleByChannel(
        HitResultLeft,
        FVector(BottomLeft, 0.0f),
        FVector(TopLeft, 0.0f),
        ECC_Visibility
    );

    // Check if all traces hit something, indicating a closed shape
    if (HitResultTop.bBlockingHit && HitResultRight.bBlockingHit &&
        HitResultBottom.bBlockingHit && HitResultLeft.bBlockingHit)
    {
        // You can draw the square or perform other actions here

        // DrawDebugLine for visualization (optional)
        DrawDebugLine(
            GetWorld(),
            FVector(TopLeft, 0.0f),
            FVector(TopRight, 0.0f),
            FColor::Green, false, -1, 0, 2.0f
        );
       DrawDebugLine(
            GetWorld(),
            FVector(TopRight, 0.0f),
            FVector(BottomRight, 0.0f),
            FColor::Green, false, -1, 0, 2.0f
        );
        DrawDebugLine(
            GetWorld(),
            FVector(BottomRight, 0.0f),
            FVector(BottomLeft, 0.0f),
            FColor::Green, false, -1, 0, 2.0f
        );
        DrawDebugLine(
            GetWorld(),
            FVector(BottomLeft, 0.0f),
            FVector(TopLeft, 0.0f),
            FColor::Green, false, -1, 0, 2.0f
        );
    }
    */

}

void AUserController::UpdateBoxSelection()
{

	
	FVector2D BoxSelectionMouse;

	if (GetMousePosition(BoxSelectionMouse.X, BoxSelectionMouse.Y))
	{
		FString MousePosString = FString::Printf(
			TEXT("Mouse Position: X=%.2f, Y=%.2f"), BoxSelectionMouse.X, BoxSelectionMouse.Y);

		UE_LOG(LogTemp, Warning, TEXT("%s"), *MousePosString);

		// draw a debug box 
		FVector DebugBoxExtent(10.1f, 10.1f, 10.1f);

		//FVector DebugBoxLocation(BoxSelectionMouse.X, BoxSelectionMouse.Y, 0.0f);

		// Get the screen space position of the mouse
		const FVector2D ScreenSpaceMouse(BoxSelectionMouse.X, BoxSelectionMouse.Y);
		FVector WorldSpaceMouse;
		FVector WorldSpaceDirection;

		// Offset the spawn distance from the camera 
		float SpawnDistance = 3000.0f; 

		
		// Convert screen space coordinates to world space
		if (UGameplayStatics::DeprojectScreenToWorld(MyController, FIntPoint(ScreenSpaceMouse.X, ScreenSpaceMouse.Y),
		WorldSpaceMouse, WorldSpaceDirection))
		{
			// Adjust the WorldOrigin to spawn the debug box further away
			FVector SpawnLoc = WorldSpaceMouse + WorldSpaceDirection * SpawnDistance;

			// Draw a debug box at the mouse position
			DrawDebugBox(this->GetWorld(), SpawnLoc, DebugBoxExtent,
						 FQuat::Identity, FColor::Red, true, -1.0f, 0, 10.0f);

			// Log the world space position where the debug box is being drawn
			FString DebugBoxLocationString = FString::Printf(
				TEXT("Debug Box Location (World Space): X=%.2f, Y=%.2f, Z=%.2f"),
				WorldSpaceMouse.X, WorldSpaceMouse.Y, WorldSpaceMouse.Z);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *DebugBoxLocationString);
		}
		bIsSelecting = true;
	}
}

void AUserController::EndBoxSelection()
{
	bIsSelecting = false;
	UE_LOG(LogTemp, Warning, TEXT("StartBoxSelection ended"));

	FVector2D SingleSelectionMouse;

	if (GetMousePosition(SingleSelectionMouse.X, SingleSelectionMouse.Y))
	{
		FString MousePosString = FString::Printf(
			TEXT("SingleSelectionMouse Position ended: X=%.2f, Y=%.2f"), SingleSelectionMouse.X, SingleSelectionMouse.Y);

		UE_LOG(LogTemp, Warning, TEXT("%s"), *MousePosString);

		
	}


	
}




/*// Convert BoxSize to FString
	FString BoxSizeString = FString::Printf(TEXT("Box Size: X=%.2f, Y=%.2f"), BoxSize.X, BoxSize.Y);
	
	// Print the FString to the GEngine output log
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, BoxSizeString);*/