// Fill out your copyright notice in the Description page of Project Settings.


#include "UserController.h"

#include "InteractiveToolManager.h"
#include "UserCharacter.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TestObjects/SelectionPawn.h"


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
	
	SelectionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SelectionArea"));
	SelectionArea->SetBoxExtent(FVector(0));

	
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

void AUserController::ZoomIn(float AxisValue)
{

	if(AxisValue == 0.f)
	{
		return;
	}

	const float Zoom = AxisValue * 100.f;
	TargetZoom = FMath::Clamp(Zoom + TargetZoom, MinZoom, MaxZoom);
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

	UE_LOG(LogTemp, Warning, TEXT("UserCh: %s"), *GetNameSafe(UserCh)); // Returns None??
	
	if(UserCh && UserCh->CameraBoom)
	{
		
		// zoom the camera in the desired direction
		const float InterpolatedZoom =  UKismetMathLibrary::FInterpTo(UserCh->CameraBoom->TargetArmLength, TargetZoom, DeltaTime, ZoomSpeed);
		UserCh->CameraBoom->TargetArmLength = InterpolatedZoom;
	}
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
	InputComponent->BindAction("MultiSelection", IE_Pressed, this, &AUserController::MultiSelect);
	InputComponent->BindAction("UpdateBoxSelection", IE_Released, this, &AUserController::EndBoxSelection);
}

void AUserController::StartBoxSelection()
{
	// Get the Coordinates of the mouse when clicked
	if (GetMousePosition(InitialMousePosition.X, InitialMousePosition.Y))
	{
		bIsSelecting = true;
		UnitSelection();
		if(bNotHit)
		{
			SelectedUnits.Empty();
			UE_LOG(LogTemp, Warning, TEXT("Selected Units: %d"), SelectedUnits.Num());
		}
	}
}


void AUserController::EndBoxSelection()
{
	bIsSelecting = false;
	//UE_LOG(LogTemp, Warning, TEXT("StartBoxSelection ended"));
	CursorMoved = false;
	FVector2D SingleSelectionMouse;
	MultiselectCond = false;
	if (GetMousePosition(SingleSelectionMouse.X, SingleSelectionMouse.Y))
	{
		//FString MousePosString = FString::Printf(
		//	TEXT("SingleSelectionMouse Position ended: X=%.2f, Y=%.2f"), SingleSelectionMouse.X, SingleSelectionMouse.Y);

		//UE_LOG(LogTemp, Warning, TEXT("%s"), *MousePosString);


		// Maybe move this to the function on when we deselect instead of ending the click 
		// Clear the array at the end of the function
		//ActorsInSelection.Empty();
	}
}


void AUserController::MultiSelect()
{
	//UE_LOG(LogTemp, Warning, TEXT("Single Click"));
	
	// Get the Coordinates of the mouse when clicked
	if (GetMousePosition(InitialMousePosition.X, InitialMousePosition.Y))
	{
		MultiselectCond = true;
		UnitSelection();
	}
}


bool AUserController::HasCursorMoved()
{
	FVector2D CurrentCursor;
	GetMousePosition(CurrentCursor.X, CurrentCursor.Y);

	// Compares The current cursor location with the first cursor location
	if(CurrentCursor != InitialMousePosition)
	{
		CursorMoved = true;
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
				bNotHit = false;
			}
			bNotHit = true;
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

		if(MultiselectCond)
		{
			SelectedUnits.AddUnique(HitPawn);
			for (AActor* HitPawn : SelectedUnits)
			{
				UE_LOG(LogTemp, Warning, TEXT("Selected Unit: %s"), *HitPawn->GetName());
			}
			UE_LOG(LogTemp, Warning, TEXT("Selected Units: %d"), SelectedUnits.Num());
		}
	}
}


void AUserController::UpdateFlow()
{
	if (bIsSelecting)
	{
		// Checks if the mouse has been moved
		if (HasCursorMoved())
		{
			FVector MouseWorldStart, MouseWorldDirection;
			
			// Checks the Current mouse position in Comparison to the Initial Mouse Position 
			if (GetMousePosition(NewMousePosition.X, NewMousePosition.Y))
			{
				APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
				if (PlayerController &&
						   PlayerController->DeprojectScreenPositionToWorld(InitialMousePosition.X, InitialMousePosition.Y, MouseWorldStart, MouseWorldDirection))
				{

					// Deproject current screen coordinates to world coordinates
					FVector CurrentMouseWorldLocation, CurrentMouseWorldDirection;
					PlayerController->DeprojectScreenPositionToWorld(NewMousePosition.X, NewMousePosition.Y, CurrentMouseWorldLocation, CurrentMouseWorldDirection);
					
					// Calculate the extent of the rectangle in X and Y directions
					float SelectionWidth = FMath::Abs(NewMousePosition.X - InitialMousePosition.X);
					float SelectionHeight = FMath::Abs(NewMousePosition.Y - InitialMousePosition.Y);

					// Find the other two edges of the rectangle
					FVector2D Edge1(InitialMousePosition.X + SelectionWidth, InitialMousePosition.Y);
					FVector2D Edge2(InitialMousePosition.X, InitialMousePosition.Y + SelectionHeight);
					
					/*
					FVector BoxExtent = FVector(SelectionWidth / 2, SelectionHeight / 2, 20);

					// Add an offset to the starting position of the box (adjust the offset as needed)
					FVector BoxSpawnLocation = MouseWorldStart + FVector(0.0f, 0.0f, 1000.0f);
					
					// Draw a debug box at the initial mouse position with dynamic scaling
					DrawDebugBox(GetWorld(), BoxSpawnLocation, BoxExtent, FQuat::Identity, FColor::Red, true, -1.0f, 0, 10.0f);
					*/
					
					// Create a box representing the selection rectangle
					FBox2D SelectionBox(InitialMousePosition, NewMousePosition);
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASelectionPawn::StaticClass(), ActorsInSelection);

					for (AActor* Actor : ActorsInSelection)
					{
						// Get the actor's 2D location
						FVector2D ActorLocation(Actor->GetActorLocation().X, Actor->GetActorLocation().Y);

						// Check if the actor is within the selection box and of the correct type
						if (SelectionBox.IsInside(ActorLocation) && Actor->IsA(ASelectionPawn::StaticClass()))
						{
							UE_LOG(LogTemp, Warning, TEXT("Selected Actor: %s"), *Actor->GetName());
						}
					}

					// Log the locations of the edges
					UE_LOG(LogTemp, Warning, TEXT("Start: (%.2f, %.2f)"), InitialMousePosition.X, InitialMousePosition.Y);
					UE_LOG(LogTemp, Warning, TEXT("Edge1: (%.2f, %.2f)"), Edge1.X, Edge1.Y);
					UE_LOG(LogTemp, Warning, TEXT("Edge2: (%.2f, %.2f)"), Edge2.X, Edge2.Y);
					UE_LOG(LogTemp, Warning, TEXT("End: (%.2f, %.2f)"), NewMousePosition.X, NewMousePosition.Y);
					
				}
			}
		}
	}
}
