// Fill out your copyright notice in the Description page of Project Settings.


#include "UserController.h"
#include "AIController.h"
#include "UserCharacter.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

class EbuildingTypes;

#define mTraceChannel ECollisionChannel::ECC_Pawn

//#include "InteractiveToolManager.h"
AUserController::AUserController()
{


	
	// Shows the mouse cursor && Handle it should use. 
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;

	// Used to check if we are drawing or selecting units.
	bIsSelecting = false;

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
	const bool bCursorOnScreen = MousePosition.X >= 0.0f && MousePosition.X <= static_cast<float>(ViewportSizeX)
		&& MousePosition.Y >= 0.0f && MousePosition.Y <= static_cast<float>(ViewportSizeY);

	bCheckCursor = bCursorOnScreen;

	// Actions to take is the cursor is on the screen
	if (bCursorOnScreen)
	{
		const FString MousePosString = FString::Printf(
			TEXT("Mouse Position: X=%.2f, Y=%.2f"), MousePosition.X, MousePosition.Y);

		// Draw the string on the screen
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::White, MousePosString);

		// GONNA NEED TO DO A CHECK TO SEE IF WE ARE HOVERING OVER A BUTTON LATER
		if (MousePosition.X < 70)
		{
			// Moves the camera to the left
			const FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
			FVector LeftVector = FVector::CrossProduct(ForwardVector, FVector::UpVector);
			LeftVector.Normalize();
			MoveCamera(LeftVector);

			bCursorMove = true;
		}
		else if (MousePosition.X > 1850)
		{
			// Moves Camera to the right
			const FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
			FVector RightVector = -FVector::CrossProduct(ForwardVector, FVector::UpVector);
			RightVector.Normalize();
			MoveCamera(RightVector);


			bCursorMove = true;
		}

		// Move Forward
		if (MousePosition.Y < 50)
		{
			const FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
			MoveCamera(ForwardVector);

			bCursorMove = true;
		}
		else if (MousePosition.Y > 920)
		{
			// Backwards
			const FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
			const FVector OppositeForwardVector = -ForwardVector;
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
		const FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
		MoveCamera(ForwardVector);
	}
}

void AUserController::EdgeScrolling_WASD_Down(float Value)
{
	if (Value)
	{
		const FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
		const FVector OppositeForwardVector = -ForwardVector;
		MoveCamera(OppositeForwardVector);
	}
}

void AUserController::EdgeScrolling_WASD_Right(float Value)
{
	if (Value)
	{
		const FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
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
		const FVector ForwardVector = UserCharacter->TopDownCameraComponent->GetForwardVector();
		FVector LeftVector = FVector::CrossProduct(ForwardVector, FVector::UpVector);
		LeftVector.Normalize();
		MoveCamera(LeftVector);
		//MoveCamera(FVector(0.0f, -2.0f, 0.0f));
	}
}

void AUserController::MoveCamera(const FVector& Direction)
{
	if (AActor* ViewTarget = GetViewTarget())
	{
		if (bCursorMove)
		{
			const float CameraSpeed = 500;
			// Get the current view target location
			const FVector NewCameraLocation = ViewTarget->GetActorLocation() + Direction * CameraSpeed * GetWorld()->
				GetDeltaSeconds();

			// Set the new view target location
			ViewTarget->SetActorLocation(NewCameraLocation);
		}
		else
		{
			const float CameraSpeed = 1000;
			// Get the current view target location
			const FVector NewCameraLocation = ViewTarget->GetActorLocation() + Direction * CameraSpeed * GetWorld()->
				GetDeltaSeconds();

			// Set the new view target location
			ViewTarget->SetActorLocation(NewCameraLocation);
		}
	}
}

void AUserController::CursorToWidget()
{
	
}


void AUserController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Unit Selection (ForLoopAtEnd?): %d"), SelectedUnits.Num());
	//UE_LOG(LogTemp, Warning, TEXT("Building Selection (ForLoopAtEnd?): %d"), SelectedBuilding.Num());
	//UE_LOG(LogTemp, Warning, TEXT("L %d"), SelectedBuilding.Num());
	
	EdgeScrolling();
	UpdateFlow();

	// Defined User Macro, Gets Trace to pawn under cursor. 
	GetHitResultUnderCursor(mTraceChannel, true, bHit);
}

void AUserController::BeginPlay()
{
	Super::BeginPlay();

	UserCharacter = Cast<AUserCharacter>(GetPawn());
	
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
	// Get the Coordinates of the mouse when clicked
	if (GetMousePosition(InitialMousePosition.X, InitialMousePosition.Y))
	{
		bIsSelecting = true;

		CastToActor();
	}
}


void AUserController::EndBoxSelection()
{
	bIsSelecting = false;
	CursorMoved = false;
	MultiselectCond = false;
	bIsDecalSelect = false;

	
	UE_LOG(LogTemp, Warning, TEXT("L: 324 -  EndBox - Building Array Count BEFORE NOT HIT: %d"), SelectedBuilding.Num());
	
	if (bNotHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("L: Nothit %d"), SelectedBuilding.Num());
		SelectionInterface->NotHit(SelectedBuilding);

		//  loops through all the actors in the class 
		for (AActor* Actor : SelectedUnits)
		{
			// makes sure they are GenAi class
			if (const AGenericBaseAI* GenAI = Cast<AGenericBaseAI>(Actor))
			{
				// turns vis off
				GenAI->SelectedDecalComp->SetVisibility(false);
			}
		}
		SelectedUnits.Empty();
		//UE_LOG(LogTemp, Warning, TEXT("L: 331 - StartBox - NoHit - End Function Unit Array Count: %d"), SelectedUnits.Num());
		UE_LOG(LogTemp, Warning, TEXT("L: 208 - Tick - NumOfBuildingAfterEmpty: %d"), SelectedBuilding.Num());
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("L: 347 - EndBox - Unit Array Count: %d"), SelectedUnits.Num());
	UE_LOG(LogTemp, Warning, TEXT("L: 348 -  EndBox - Building Array Count AFTER NOT HIT : %d"), SelectedBuilding.Num());

	
	// At the end of each selection we check what units are selected so then
	// We can communicate the units in the array to the BTTask Nodes
	/*if (BlackboardComponent)
	{
		/*const FBlackboard::FKey ArrayKeyID = BlackboardComponent->GetKeyID(ArrayKeyID)
		// Set the array value in the Blackboard
		BlackboardComponent->SetValueAsObject(ArrayKeyID, SelectedUnits);#1#
	}*/
}


void AUserController::MultiSelect()
{
	// Get the Coordinates of the mouse when clicked
	if (GetMousePosition(InitialMousePosition.X, InitialMousePosition.Y))
	{
		MultiselectCond = true;
		UE_LOG(LogTemp, Warning, TEXT("Multi - True"));
		CastToActor();
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
	}
	return false;
}


void AUserController::CastToActor()
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
			// draw a debug box at the hit location
			DrawDebugBox(GetWorld(), HitResult.Location, DebugBoxExtent, FQuat::Identity, FColor::Red, false, 2.0f, 0,
			             5.0f);
			
			MouseStart = bHit.Location;
			if (AActor* HitActor = HitResult.GetActor())
			{
				HandleSelection(HitActor);
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

void AUserController::HandleSelection(AActor* ActorHit)
{
	if (ActorHit)
	{
		// If it isn't multi-select, empty the array first
		if (MultiselectCond)
		{
			UE_LOG(LogTemp, Warning, TEXT("L: 508 - HandlePawn - before MultiUnitSelection: %d"),
			       SelectedBuilding.Num());
			SelectionInterface->MultiUnitSelection(SelectedUnits, ActorHit);
		}
		else if (ActorHit->Tags.Contains("Building"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Building"));

			if (SelectedBuilding.IsEmpty())
			{
				SelectionInterface->BuildingArrayIsEmpty(SelectedBuilding, ActorHit);
			}
			else if (SelectedBuilding.Num() > 0)
			{
				SelectionInterface->ChangeElementInBuildingArray(SelectedBuilding, ActorHit);
			}
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("DOES NOT HAVE TAG!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
			bNotHit = true;
		}
	}
}


TArray<AActor*> AUserController::ConvertPawnArrayToActorArray(const TArray<APawn*>& PawnArray)
{
	TArray<AActor*> ActorArray;

	for (APawn* Src : PawnArray)
	{
		// Since APawn is a subclass of AActor, you can directly add it to the ActorArray
		ActorArray.Add(Src);
	}

	return ActorArray;
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

					// Create an array to store actors that need to be removed
					TArray<AActor*> ActorsToRemove;

					// iterate over all previously selected units stored in the SU array.
					for (AActor* SelectedActor : SelectedUnits)
					{
						// For each selected actor we check if it's still present in the ActorsToBeFound array.
						// (ie. still overlapping with the selection area).
						if (!ActorsToBeFound.Contains(SelectedActor))
						{
							// If the actor is not found in the ATBF array, it's no longer overlapping,
							// so we deselect it by hiding its selection decal and marking it for removal.
							if (const AGenericBaseAI* AI = Cast<AGenericBaseAI>(SelectedActor))
							{
								AI->SelectedDecalComp->SetVisibility(false);
							}
							ActorsToRemove.Add(SelectedActor);
						}
					}

					// Remove the actors that need to be removed
					for (AActor* ActorToRemove : ActorsToRemove)
					{
						SelectedUnits.Remove(ActorToRemove);
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

/*// retrieve all actors currently overlapping with the selection area and store them in the ATBF array.
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
}*/