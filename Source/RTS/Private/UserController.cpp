// Fill out your copyright notice in the Description page of Project Settings.


#include "UserController.h"

#include "InteractiveToolManager.h"
#include "UserCharacter.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/DecalComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


AUserController::AUserController()
{
	// Shows the mouse cursor && Handle it should use. 
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;

	// Used to check if we are drawing or selecting units.
	bIsSelecting = false;

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	
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
	UpdateFlow();
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

// We Use this function to select an item or unit.
// ONLY Draw a square if the coordinates start moving. 

// Get initial Mouse Coordinates
// Then do Logic
// Unless, if the mouse coordinates change while pressing down the input
// So do an if statement to check if the mouse if moving.
	
// When just clicking, Shoot a line trace from the camera to the object you want to pick, This will work as single use selection then use if statement for multi.........

void AUserController::StartBoxSelection()
{
	// Get the Coordinates of the mouse when clicked
	if (GetMousePosition(InitialMousePosition.X, InitialMousePosition.Y))
	{
		FString MousePosString = FString::Printf(
			TEXT("SingleSelectionMouse Position: X=%.2f, Y=%.2f"), InitialMousePosition.X, InitialMousePosition.Y);

		UE_LOG(LogTemp, Warning, TEXT("%s"), *MousePosString);

		bIsSelecting = true;
		UE_LOG(LogTemp, Warning, TEXT("Single Click"));

		UnitSelection();


		
		/*if (Hit){
			if (AActor* Actor)
			{
				UnitSelection();
			}
		}*/
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

void AUserController::UnitSelection()
{
	FVector WorldMouseLocation, WorldMouseDirection;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	// Get the mouse cursor position in world space
	if (UGameplayStatics::DeprojectScreenToWorld(PlayerController, FVector2D(InitialMousePosition.X, InitialMousePosition.Y), WorldMouseLocation, WorldMouseDirection))
	{
		// Perform a line trace to detect pawns
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this); // Ignore the controller itself
		
		float TraceDistance = 7000.f;
		
		// Adjust the WorldOrigin to spawn the debug box further away
		FVector SpawnLoc = WorldMouseLocation + WorldMouseDirection * TraceDistance;
		
		FVector DebugBoxExtent(50.0f, 50.0f, 50.0f);
		
		if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldMouseLocation, WorldMouseLocation + WorldMouseDirection * TraceDistance, ECC_Visibility, CollisionParams))
		{
			// Check if the hit actor is a pawn
			APawn* HitPawn = Cast<APawn>(HitResult.GetActor());

			// Check if its either
			// Damageable
			// Resource
			
			if (HitPawn)
			{
				// Perform actions for the selected pawn
				HandlePawnSelection(HitPawn);
				DrawDebugBox(GetWorld(), SpawnLoc, DebugBoxExtent, FColor::Green, false, -1, 0, 4);
				
			}
		}
	}
}

void AUserController::HandlePawnSelection(APawn* HitPawn)
{
	if (HitPawn)
	{
		// Log information about the selected pawn
		FString PawnName = HitPawn->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Selected Pawn: %s"), *PawnName);

		// Perform additional actions for the selected pawn if needed
	}
}


void AUserController::UpdateFlow()
{
	if (bIsSelecting)
	{
		// Checks if the mouse has been moved
		if (HasCursorMoved())
		{
			// Checks the Current mouse position in Comparison to the Initial Mouse Position 
			
			if (GetMousePosition(NewMousePosition.X, NewMousePosition.Y))
			{
				// Calculate the extent of the rectangle in X and Y directions
				float SelectionWidth = FMath::Abs(NewMousePosition.X - InitialMousePosition.X);
				float SelectionHeight = FMath::Abs(NewMousePosition.Y - InitialMousePosition.Y);

				// Find the other two edges of the rectangle
				FVector2D Edge1(InitialMousePosition.X + SelectionWidth, InitialMousePosition.Y);
				FVector2D Edge2(InitialMousePosition.X, InitialMousePosition.Y + SelectionHeight);

				// Log the locations of the edges
				UE_LOG(LogTemp, Warning, TEXT("Start: (%.2f, %.2f)"), InitialMousePosition.X, InitialMousePosition.Y);
				UE_LOG(LogTemp, Warning, TEXT("Edge1: (%.2f, %.2f)"), Edge1.X, Edge1.Y);
				UE_LOG(LogTemp, Warning, TEXT("Edge2: (%.2f, %.2f)"), Edge2.X, Edge2.Y);
				UE_LOG(LogTemp, Warning, TEXT("End: (%.2f, %.2f)"), NewMousePosition.X, NewMousePosition.Y);

				FVector WorldSpaceMouse;
				FVector WorldSpaceDirection;
				float SpawnDistance = 1000.f;

				/*if (UGameplayStatics::DeprojectScreenToWorld(MyController,
															 FIntPoint(InitialMousePosition.X, InitialMousePosition.Y),
															 WorldSpaceMouse, WorldSpaceDirection))
				{
					// Adjust the WorldOrigin to spawn the debug box further away
					FVector SpawnLoc = WorldSpaceMouse + WorldSpaceDirection * SpawnDistance;

					// Draw lines connecting the edges to form a square
					DrawDebugLine(GetWorld(), FVector(InitialMousePosition.X, InitialMousePosition.Y, 0.0f),
								  FVector(Edge1.X, Edge1.Y, 0.0f), FColor::Green, false, -1, 0, 2.0f);
					DrawDebugLine(GetWorld(), FVector(Edge1.X, Edge1.Y, 0.0f),
								  FVector(NewMousePosition.X, NewMousePosition.Y, 0.0f), FColor::Green, false, -1, 0,
								  2.0f);
					DrawDebugLine(GetWorld(), FVector(NewMousePosition.X, NewMousePosition.Y, 0.0f),
								  FVector(Edge2.X, Edge2.Y, 0.0f), FColor::Green, false, -1, 0, 2.0f);
					DrawDebugLine(GetWorld(), FVector(Edge2.X, Edge2.Y, 0.0f),
								  FVector(InitialMousePosition.X, InitialMousePosition.Y, 0.0f), FColor::Green, false,
								  -1, 0, 2.0f);
				}*/
			}
		}
	}
}


void AUserController::Draw2DSSquare(const FVector Edge1, FVector2D& Edge2) // Direction?? 
{
	// Draw Line from Start to Edge 1 & edge 2
	if(InitialMousePosition.X && InitialMousePosition.Y)
	{
		DrawDebugLine(GetWorld(), FVector(InitialMousePosition.X), Edge1, FColor::Red);
	}
}



/*
void AUserController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	GetHitResultUnderCursor(mTraceChannel, true, hit);
	CalculateMovement(DeltaTime);

	// keep updating the destination every tick while desired
	if (leftMouseDown)
	{
		//MoveToMouseCursor();
		mouseDownTime += DeltaTime;

		mouseEnd = hit.Location;

		centerMouseLocation = FVector((mouseStart + mouseEnd) / 2);
		dist = FVector::Dist(mouseEnd, mouseStart) / 2;
		selectionSize = FVector(dist, dist, 100);

		if (mouseDownTime > 0.75f)
			DrawDebugBox(GetWorld(), centerMouseLocation, selectionSize, FQuat(0, 0, 0, 0), FColor::Black);
	}
	else {
		mouseDownTime = 0;
	}

	if (CursorToWorld != nullptr)
	{
		FVector CursorFV = hit.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
		CursorToWorld->SetWorldLocation(hit.Location);
		CursorToWorld->SetWorldRotation(CursorR);

		if (hit.bBlockingHit)
		{
			AActor* targetFound = hit.GetActor();

			if (targetFound != nullptr && targetFound->Implements<UResourceInterface>())
			{
				IResourceInterface* ri = GetResource(targetFound);
				UMaterial* decal = *materialCursors.Find(ri->GetType());

				if (decal != nullptr)
					CursorToWorld->SetDecalMaterial(decal);
			}
		}
	}
}
*/
