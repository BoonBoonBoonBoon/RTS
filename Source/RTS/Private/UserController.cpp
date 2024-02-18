// Fill out your copyright notice in the Description page of Project Settings.


#include "UserController.h"

#include "AIController.h"
#include "UserCharacter.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Buildings/BarracksBuilding.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"


#define mTraceChannel ECollisionChannel::ECC_Pawn

//#include "InteractiveToolManager.h"
AUserController::AUserController()
{
	// Shows the mouse cursor && Handle it should use. 
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;

	// Used to check if we are drawing or selecting units.
	bIsSelecting = false;

	// Create a decal in the world to show the cursor's location
	/*CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	*/

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
		if (MousePosition.X < 70)
		{
			// Moves the camera to the left
			FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
			FVector LeftVector = FVector::CrossProduct(ForwardVector, FVector::UpVector);
			LeftVector.Normalize();
			MoveCamera(LeftVector);

			bCursorMove = true;
		}
		else if (MousePosition.X > 1850)
		{
			// Moves Camera to the right
			FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
			FVector RightVector = -FVector::CrossProduct(ForwardVector, FVector::UpVector);
			RightVector.Normalize();
			MoveCamera(RightVector);


			bCursorMove = true;
		}

		// Move Forward
		if (MousePosition.Y < 50)
		{
			FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
			MoveCamera(ForwardVector);

			bCursorMove = true;
		}
		else if (MousePosition.Y > 920)
		{
			// Backwards
			FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
			FVector OppositeForwardVector = -ForwardVector;
			MoveCamera(OppositeForwardVector);

			bCursorMove = true;
		}

		bCursorMove = false;
	}
}

void AUserController::EdgeScrolling_WASD_Up(float Value)
{
	if (Value)
	{
		FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
		MoveCamera(ForwardVector);
	}
}

void AUserController::EdgeScrolling_WASD_Down(float Value)
{
	if (Value)
	{
		FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
		FVector OppositeForwardVector = -ForwardVector;
		MoveCamera(OppositeForwardVector);
	}
}

void AUserController::EdgeScrolling_WASD_Right(float Value)
{
	if (Value)
	{
		FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
		FVector RightVector = -FVector::CrossProduct(ForwardVector, FVector::UpVector);
		RightVector.Normalize();
		MoveCamera(RightVector);
		//MoveCamera(FVector(0.0f, 2.0f, 0.0f));
	}
}

void AUserController::EdgeScrolling_WASD_Left(float Value)
{
	if (Value)
	{
		FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
		FVector LeftVector = FVector::CrossProduct(ForwardVector, FVector::UpVector);
		LeftVector.Normalize();
		MoveCamera(LeftVector);
		//MoveCamera(FVector(0.0f, -2.0f, 0.0f));
	}
}

void AUserController::MoveCamera(const FVector& Direction)
{
	// Returns the current view target 
	//APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(GetViewTarget());

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

void AUserController::CursorToWidget()
{
	
}


void AUserController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// Checks if we are valid to dispose of the selection decal
	/*if (MultiselectCond)
	{
		CleanUpDecal(NULL);
	}*/
	EdgeScrolling();
	UpdateFlow();

	// Defined User Macro, Gets Trace to pawn under cursor. 
	GetHitResultUnderCursor(mTraceChannel, true, bHit);
}

void AUserController::BeginPlay()
{
	Super::BeginPlay();

	UserCharacter = Cast<AUserCharacter>(GetPawn());


	// Quick fills the array, Will be removed on first interaction.
	//AActor* TempActor = nullptr;
	//SelectedUnits.Add(TempActor);
}

void AUserController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Controls The Camera Movement 
	InputComponent->BindAxis("Up", this, &AUserController::EdgeScrolling_WASD_Up);
	InputComponent->BindAxis("Down", this, &AUserController::EdgeScrolling_WASD_Down);
	InputComponent->BindAxis("Right", this, &AUserController::EdgeScrolling_WASD_Right);
	InputComponent->BindAxis("Left", this, &AUserController::EdgeScrolling_WASD_Left);

	// Draw Box and select units 
	InputComponent->BindAction("BoxSelection", IE_Pressed, this, &AUserController::StartBoxSelection);
	InputComponent->BindAction("MultiSelection", IE_Pressed, this, &AUserController::MultiSelect);
	InputComponent->BindAction("UpdateBoxSelection", IE_Released, this, &AUserController::EndBoxSelection);

	InputComponent->BindAction("ActionKey", IE_Pressed, this, &AUserController::EventKey);
}


void AUserController::EventKey()
{
	// Get where is being clicked.
	if (GetMousePosition(InitialMousePosition.X, InitialMousePosition.Y))
	{
		FVector WorldMouseLocation, WorldMouseDirection;
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		// Get the mouse cursor position in world space
		if (UGameplayStatics::DeprojectScreenToWorld(PlayerController,
		                                             FVector2D(InitialMousePosition.X, InitialMousePosition.Y),
		                                             WorldMouseLocation, WorldMouseDirection))
		{
			// Perform a line trace to detect pawns
			FHitResult HitResult;
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(this); // Ignore the controller itself

			float TraceDistance = 7000.f;

			FVector DebugBoxExtent(50.0f, 50.0f, 50.0f);

			if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldMouseLocation,
			                                         WorldMouseLocation + WorldMouseDirection * TraceDistance,
			                                         ECC_Visibility, CollisionParams))
			{
				// Check if the hit actor is a pawn
				// ReSharper disable once CppDeclaratorNeverUsed
				if (APawn* HitPawn = Cast<APawn>(HitResult.GetActor()))
				{
					// Draw a debug box at the hit location
					DrawDebugBox(GetWorld(), HitResult.Location, DebugBoxExtent, FQuat::Identity, FColor::Green, false,
					             1, 0, 5.0f);

					// Then call function with location to move units too
					UE_LOG(LogTemp, Warning, TEXT("Hit Pawn"));
				}
				else
				{
					// Draw a debug box at the hit location
					DrawDebugBox(GetWorld(), HitResult.Location, DebugBoxExtent, FQuat::Identity, FColor::Green, false,
					             1, 0, 5.0f);
					UE_LOG(LogTemp, Warning, TEXT("Hit Ground"));

					FVector Location = HitResult.Location;

					UE_LOG(LogTemp, Warning, TEXT("Address %p"), &Location);
					// if the array has a unit in it 
					if (SelectedUnits.Num() > 0)
					{
						for (AActor* Actor : SelectedUnits)
						{
							if (const AGenericBaseAI* GenAI = Cast<AGenericBaseAI>(Actor))
							{
								// Check if the actor has a va  lid controller
								if (AController* GenController = GenAI->GetController())
								{
									// Check the class of the controller
									if (GenController->IsA<AController>())
									{
										AAIController* Con = Cast<AAIController>(GenAI->GetController());
										if (Con)
										{
											GenAI->LocationToMove = Location;
											GenAI->ValidHit = true;

											// Waypoint 
											//;pWayPointActor->SpawnActorLocation(HitResult.Location);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void AUserController::StartBoxSelection()
{
	/* Set this up at somepoint, can setup double click, this move camera around.*/
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, TargetLocation);

	// Get the Coordinates of the mouse when clicked
	if (GetMousePosition(InitialMousePosition.X, InitialMousePosition.Y))
	{
		bIsSelecting = true;
		UnitSelection();

		if (bNotHit)
		{
			//  loops through all the actors in the class 
			for (AActor* Actor : SelectedUnits)
			{
				// makes sure they are GenAi class
				if (const AGenericBaseAI* GenAI = Cast<AGenericBaseAI>(Actor))
				{
					// turns vis off
					GenAI->SelectedDecalComp->SetVisibility(false);
					//UE_LOG(LogTemp, Warning, TEXT("Selected Units: %d"), SelectedUnits.Num());
					UE_LOG(LogTemp, Warning, TEXT("Array Wiped"));
				}
			}
			// Clear the SelectedUnits array after processing all elements
			SelectedUnits.Empty();
		}
	}
}


void AUserController::EndBoxSelection()
{
	bIsSelecting = false;
	//UE_LOG(LogTemp, Warning, TEXT("StartBoxSelection ended"));
	CursorMoved = false;
	//FVector2D SingleSelectionMouse;
	MultiselectCond = false;
	bIsDecalSelect = false;

	// At the end of each selection we check what units are selected so then
	// We can communicate the units in the array to the BTTask Nodes
	if (BlackboardComponent)
	{
		/*const FBlackboard::FKey ArrayKeyID = BlackboardComponent->GetKeyID(ArrayKeyID)
		// Set the array value in the Blackboard
		BlackboardComponent->SetValueAsObject(ArrayKeyID, SelectedUnits);*/
	}
}


void AUserController::MultiSelect()
{
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
	if (CurrentCursor != InitialMousePosition)
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
	if (UGameplayStatics::DeprojectScreenToWorld(PlayerController,
	                                             FVector2D(InitialMousePosition.X, InitialMousePosition.Y),
	                                             WorldMouseLocation, WorldMouseDirection))
	{
		// Perform a line trace to detect pawns
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this); // Ignore the controller itself

		float TraceDistance = 7000.f;

		// Adjust the WorldOrigin to spawn the debug box further away
		FVector SpawnLoc = WorldMouseLocation + WorldMouseDirection * TraceDistance;

		FVector DebugBoxExtent(50.0f, 50.0f, 50.0f);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldMouseLocation,
		                                         WorldMouseLocation + WorldMouseDirection * TraceDistance,
		                                         ECC_Visibility, CollisionParams))
		{
			// The Spawn Location for the collison box to spawn
			//BoxHitLocation = HitResult.Location;
			MouseStart = bHit.Location;
			//GetHitResultUnderCursor()
			// Check if its either
			// Damageable
			// Resource

			// Checks if multiselect, if so we dont need to click off deselect

			// Want it so when i select with single or multi it will select.
			// But if i dont multiselect the next one it will just move the next one.
			//

			// Check if the hit actor is a pawn
			APawn* HitPawn = Cast<APawn>(HitResult.GetActor());
			if (HitPawn)
			{
				
				if(AMainBuilding* HitBuilding = Cast<AMainBuilding>(HitPawn))
				{
					if (HitBuilding->BuildingType == EBuildingTypes::Barracks)
					{
						BuildingInterface->SpawnUnit(); 
					}
				}
				
				// Works -- But i dont why this Enum would work then
				// Since i will have to cast everytime i want to use it???
				// maybe this should only be done in the MainBuilding Cast?
				// Moved it into main building, but now im consufed because how can we then define
				// The children class of a certain building type? 
				
				/*if (HitBuilding && HitBuilding->BuildingType == EBuildingTypes::Barracks)
				{*/
				
				// Check if it is of Type Barracks
				/*//if(ABarracksBuilding* Barracks = Cast<ABarracksBuilding>(HitPawn))
				if (HitPawn->IsA(ABarracksBuilding::StaticClass())) // Check if HitPawn is of type ABarracks
				{
					// HitPawn is of type ABarracks
					// use EBuildingTypes enum for further processing
					EBuildingTypes BuildingType = EBuildingTypes::Barracks;
					
					// Spawns Unit through interface 
					BuildingInterface->SpawnUnit();
				}*/
				
				
				// Perform actions for the selected pawn
				HandlePawnSelection(HitPawn);

				// Will run no matter what 
				DrawDebugBox(GetWorld(), SpawnLoc, DebugBoxExtent, FColor::Green, false, -1, 0, 4);
				bNotHit = false;
			}
			else
			{
				bNotHit = true;
			}
		}
	}
}

void AUserController::HandlePawnSelection(APawn* HitPawn)
{
	if (HitPawn)
	{
		bIsDecalSelect = true;

		// If it isn't multi-select, empty the array first
		if (MultiselectCond)
		{
			// Loops through all possible actors 
			SelectedUnits.AddUnique(HitPawn);
			for (AActor* Src : SelectedUnits)
			{
				Src->Tags.AddUnique(TEXT("SelectedPawn"));
				if (Src->Tags.Contains(TEXT("SelectedPawn")))
				{
					if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Src))
					{
						BaseAI->SelectedDecalComp->SetVisibility(true);
						UE_LOG(LogTemp, Warning, TEXT("Selected Units: %d"), SelectedUnits.Num());
					}
				}
			}
		}
		else
		{
			// Single Left Click
			if (SelectedUnits.Num() == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("empty"));

				SelectedUnits.AddUnique(HitPawn);
				for (AActor* Src : SelectedUnits)
				{
					Src->Tags.AddUnique(TEXT("SelectedPawn"));
					if (Src->Tags.Contains(TEXT("SelectedPawn")))
					{
						if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Src))
						{
							BaseAI->SelectedDecalComp->SetVisibility(true);
							UE_LOG(LogTemp, Warning, TEXT("Selected Units: %d"), SelectedUnits.Num());
						}
					}
				}
			}
			// If it currently has a few elements 
			else if (SelectedUnits.Num() > 1 || SelectedUnits.Num() == 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("empty"));

				// Loops through all the elements and turns vis off
				for (AActor* Pawns : SelectedUnits)
				{
					if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Pawns))
					{
						BaseAI->SelectedDecalComp->SetVisibility(false);
					}
				}
				// then empties array
				SelectedUnits.Empty();

				// adds the new incoming element
				SelectedUnits.AddUnique(HitPawn);

				for (AActor* NewPawn : SelectedUnits)
				{
					if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(NewPawn))
					{
						// sets the new elements vis 
						BaseAI->SelectedDecalComp->SetVisibility(true);
					}
				}
			}
		}
	}
}

void AUserController::HandleMarqueePawnSelection(AActor* HitPawn)
{
	if (HitPawn) // Validate the Actor 
	{
		if (!SelectedUnits.Contains(HitPawn))
		{
			SelectedUnits.Add(HitPawn);

			if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(HitPawn))
			{
				BaseAI->SelectedDecalComp->SetVisibility(true);
			}
		}
	}
}


void AUserController::UnitDecals(AGenericBaseAI* HitPawn)
{
	if (HitPawn)
	{
		Decals->DecalHit = true;
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
					PlayerController->DeprojectScreenPositionToWorld(InitialMousePosition.X, InitialMousePosition.Y,
					                                                 MouseWorldStart, MouseWorldDirection))
				{
					// De-project current screen coordinates to world coordinates
					FVector CurrentMouseWorldLocation, CurrentMouseWorldDirection;
					PlayerController->DeprojectScreenPositionToWorld(NewMousePosition.X, NewMousePosition.Y,
					                                                 CurrentMouseWorldLocation,
					                                                 CurrentMouseWorldDirection);
					// The final destination of the Mouse 
					MouseEnd = bHit.Location;

					// Calculate the center location of the mouse locations 
					CenterMouseLocation = FVector((MouseStart + MouseEnd) / 2);
					dist = FVector::Dist(MouseEnd, MouseStart) / 2;
					SelectionSize = FVector(dist, dist, 100);

					//DrawDebugBox(GetWorld(), CenterMouseLocation, SelectionSize, FQuat(0,0,0,0), FColor::Black);

					SelectionArea->SetWorldLocation(CenterMouseLocation);
					SelectionArea->SetBoxExtent(SelectionSize / 2);

					// retrieve all actors currently overlapping with the selection area and store them in the ATBF array.
					TArray<AActor*> ActorsToBeFound;
					SelectionArea->GetOverlappingActors(ActorsToBeFound);

					// iterate over all previously selected units stored in the SU array.
					for (AActor* SelectedActor : SelectedUnits)
					{
						// For each selected actor we check if it's still present in the ActorsToBeFound array.
						// (ie. still overlapping with the selection area).
						if (!ActorsToBeFound.Contains(SelectedActor))
						{
							// If the actor is not found in the ATBF array,it's no longer overlapping,
							// so we deselect it by hiding its selection decal and removing it from the SU array.
							if (const AGenericBaseAI* AI = Cast<AGenericBaseAI>(SelectedActor))
							{
								AI->SelectedDecalComp->SetVisibility(false);
							}
							SelectedUnits.Remove(SelectedActor);
						}
					}

					// Iterate through newly overlapped actors and select them
					for (AActor* Actor : ActorsToBeFound)
					{
						HandleMarqueePawnSelection(Actor);
					}
				}
			}
		}
	}
}
