// Fill out your copyright notice in the Description page of Project Settings.


#include "UserController.h"
#include "AIController.h"
#include "UserCharacter.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Economy/EconomyManager.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/ResourceInterface.h"
#include "Kismet/GameplayStatics.h"

class EbuildingTypes;

#define mTraceChannel ECollisionChannel::ECC_Pawn


void AUserController::OnSwitchBarracksUI(bool bCloseBarracksUI)
{
	if (bCloseBarracksUI)
	{
		CloseMarketplaceUI.Broadcast(true);
	}
}

void AUserController::OnSwitchMarketplaceUI(bool bCloseMarketUI)
{
	if (bCloseMarketUI)
	{
		CloseBarracksUI.Broadcast(true);
	}
}

int32 AUserController::AllUnitAmountInt(TArray<AGenericBaseAI*> AllU)

{
	return GrabAllUnits.Num();
}


TArray<AActor*> AUserController::GetSelectedUnitsBP()
{
	return SelectedUnits;
}

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

	// Initialize the CombatInterface
	CombatInterface = Cast<ICombatInterface>(this);


	UWoodAmount = 0;
	UStoneAmount = 0;
	UFoodAmount = 0;
	UGoldAmount = 0;
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
			constexpr float CameraSpeed = 500;
			// Get the current view target location
			const FVector NewCameraLocation = ViewTarget->GetActorLocation() + Direction * CameraSpeed * GetWorld()->
				GetDeltaSeconds();

			// Set the new view target location
			ViewTarget->SetActorLocation(NewCameraLocation);
		}
		else
		{
			constexpr float CameraSpeed = 1000;
			// Get the current view target location
			const FVector NewCameraLocation = ViewTarget->GetActorLocation() + Direction * CameraSpeed * GetWorld()->
				GetDeltaSeconds();

			// Set the new view target location
			ViewTarget->SetActorLocation(NewCameraLocation);
		}
	}
}


void AUserController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EdgeScrolling();
	UpdateFlow();

	// Defined User Macro, Gets Trace to pawn under cursor. 
	GetHitResultUnderCursor(mTraceChannel, true, bHit);

	ARTSGameModeBase* GameMode = Cast<ARTSGameModeBase>(GetWorld()->GetAuthGameMode());

	GrabAllUnits = GameMode->GetAllFriendlyAI(GetWorld());

	AllWorldUnitsINT32 = AllUnitAmountInt(GrabAllUnits);

	// Call CheckAttackDistance every tick
	CheckAttackDistance();
	
}

void AUserController::BeginPlay()
{
	Super::BeginPlay();

	UserCharacter = Cast<AUserCharacter>(GetPawn());
	SelectedBuilding.Empty();
	bNotHit = false;

	// Initialize the CombatInterface
	CombatInterface = Cast<ICombatInterface>(this);

	SelectionInterface->CloseBarracksUISwitch.AddDynamic(this, &AUserController::OnSwitchBarracksUI);
	SelectionInterface->CloseMarketUISwitch.AddDynamic(this, &AUserController::OnSwitchMarketplaceUI);

	if (WidgetClass)
	{
		ResourceWidgetInstance = CreateWidget<UUserWidget>(this, WidgetClass);
		if (ResourceWidgetInstance)
		{
			ResourceWidgetInstance->AddToViewport();
		}
	}

	// Economy Resource Interface
	UserControllerPtr = this;
	EconomyManager = UEconomyManager::GetInstance();
	if (EconomyManager != NULL)
	{
		if (UserControllerPtr.IsValid() && UserControllerPtr != NULL)
		{
			UEconomyManager* EconomyManagerInstance = UEconomyManager::GetInstance();
			if (EconomyManagerInstance != nullptr && UserControllerPtr.IsValid())
			{
				/*UEconomyManager::GetInstance()->OnGoldChanged.AddDynamic(UserControllerPtr.Get(),
																	   &AUserController::OnGoldChanged);
																	   */

				EconomyManagerInstance->OnWoodChanged.AddDynamic(UserControllerPtr.Get(),
				                                                 &AUserController::OnWoodChanged);
				EconomyManagerInstance->OnStoneChanged.AddDynamic(UserControllerPtr.Get(),
				                                                  &AUserController::OnStoneChanged);
				EconomyManagerInstance->OnFoodChanged.AddDynamic(UserControllerPtr.Get(),
				                                                 &AUserController::OnFoodChanged);
				EconomyManagerInstance->OnGoldChanged.AddDynamic(UserControllerPtr.Get(),
				                                                 &AUserController::OnGoldChanged);
			}
		}
		else
		{
			// Log an error or handle the situation where the instance is null or the UserControllerPtr is invalid
		}
	}
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
	InputComponent->BindAction("PatrolAI", IE_Pressed, this, &AUserController::EnterPatrolMode);
}

void AUserController::CheckAttackDistance()
{
	if (CurrentTarget)
	{
		for (AActor* Unit : AttackingUnits)
		{
			float Distance = FVector::Dist(Unit->GetActorLocation(), CurrentTarget->GetActorLocation());

			// Replace 300.0f with your attack distance
			if (Distance <= 300.0f)
			{
				if (AGenericBaseAI* AIUnit = Cast<AGenericBaseAI>(Unit))
				{
					AIUnit->StartAttacking(CurrentTarget);
				}
			}
		}
	}
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
				CurrentTarget = NULL;

				if (AActor* HitActorObj = (HitResult.GetActor()))
				{
					// Check if the Hit Result is a Resource.
					if (Cast<IResourceInterface>(HitActorObj))
					{
						// Invalidate the patrol.
						bPatrolMode = false;
						PatrolPoints.Empty();

						/*// Draw a debug box at the hit location
						DrawDebugBox(GetWorld(), HitResult.Location, DebugBoxExtent, FQuat::Identity, FColor::Green,
						             false,
						             1, 0, 5.0f);*/

						HandleResourceGathering(HitActorObj);
					}
					else if (HitActorObj->Tags.Contains("Enemy"))
					{
						if (CombatInterface != nullptr)
						{
							// Store the clicked enemy as the current target
							CurrentTarget = HitActorObj;

							CombatInterface->FindEnemy(HitActorObj, SelectedUnits);
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("Null"));
						}
					}
					else
					{
						FVector Location = HitResult.Location;

						if (bPatrolMode)
						{
							// Process the Location of the hit.
							ProcessPatrolClick(HitResult);
						}
						else if (SelectedUnits.Num() > 0)
						{
							SelectionInterface->MoveGroupToLocation(SelectedUnits, Location);
						}

						/*// Draw a debug box at the hit location
						DrawDebugBox(GetWorld(), HitResult.Location, DebugBoxExtent, FQuat::Identity, FColor::Green,
						             false,
						             15, 0, 5.0f);*/
					}
				}
			}
		}
	}
}

void AUserController::HandleResourceGathering(AActor* Resource)
{
	if (IResourceInterface* ResourceInterface = Cast<IResourceInterface>(Resource))
	{
		// Return the TYPE of resource.
		AActor* ResourceActor = ResourceInterface->HandleIdentification(Resource);
		// Contains the resource we clicked on.

		if (SelectedUnits.Num() > 0)
		{
			// Loop through Worker Drones currently selected & Assign them their own Array.
			TArray<AActor*> WorkerDrones = SelectionInterface->CheckUnitTypeForGathering(SelectedUnits);

			if (!WorkerDrones.IsEmpty())
			{
				TArray<FVector> GatherPositions = ResourceInterface->CalcGatherPos(ResourceActor, WorkerDrones);

				for (int32 i = 0; i < WorkerDrones.Num(); ++i)
				{
					AActor* Drone = WorkerDrones[i];
					FVector GatherPos = GatherPositions[i];

					if (Drone)
					{
						FString DroneName = Drone->GetName();
						UE_LOG(LogTemp, Warning, TEXT("Drone %d: %s"), i, *DroneName);
					}

					MoveDronesToGatherPos(GatherPos, Drone);
				}
			}
		}
	}
}


void AUserController::MoveDronesToGatherPos(FVector GatherPos, AActor* Drone)
{
	if (const AGenericBaseAI* GenAI = Cast<AGenericBaseAI>(Drone))
	{
		// Check if the actor has a valid controller
		if (AController* GenController = GenAI->GetController())
		{
			// Check the class of the controller
			if (GenController->IsA<AController>())
			{
				AAIController* Con = Cast<AAIController>(GenAI->GetController());
				if (Con)
				{
					GenAI->LocationToMove = GatherPos;
					GenAI->ValidHit = true;
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
		SetAllUnitsTrue = false;

		bIsSelecting = true;

		CastToActor();

		// Empties the array of selectable classes.
		if (bNotHit)
		{
			SelectionInterface->NotHit(SelectedBuilding);
			SelectionInterface->NotHit(SelectedUnits);

			// Close The Widgets 
			CloseBarracksUI.Broadcast(true);
			CloseMarketplaceUI.Broadcast(true);
		}
	}
}


void AUserController::EndBoxSelection()
{
	bIsSelecting = false;
	CursorMoved = false;
	MultiselectCond = false;
	bIsDecalSelect = false;
}


void AUserController::MultiSelect()
{
	// Get the Coordinates of the mouse when clicked
	if (GetMousePosition(InitialMousePosition.X, InitialMousePosition.Y))
	{
		MultiselectCond = true;
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
			//DrawDebugBox(GetWorld(), HitResult.Location, DebugBoxExtent, FQuat::Identity, FColor::Red, false, 2.0f, 0,
			           //  5.0f);

			MouseStart = bHit.Location;
			if (AActor* HitActor = HitResult.GetActor())
			{
				bNotHit = false;
				HandleSelection(HitActor);
				//DrawDebugBox(GetWorld(), SpawnLoc, DebugBoxExtent, FColor::Green, false, -1, 0, 4);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No Actor Hit"))
				bNotHit = true;
			}
		}
	}
}

void AUserController::HandleSelection(AActor* ActorHit)
{
	if (ActorHit)
	{
		if (ActorHit->Tags.Contains("Unit")) // Look for Actor Type.
		{
			// Close the Widget.
			CloseBarracksUI.Broadcast(true);
			CloseMarketplaceUI.Broadcast(true);

			if (!SelectedBuilding.IsEmpty()) // Clears Selection to process new Array Selection.
			{
				SelectionInterface->NotHit(SelectedBuilding);
			}

			if (MultiselectCond)
			{
				SelectionInterface->MultiUnitSelection(SelectedUnits, ActorHit);
			}
			else
			{
				SelectionInterface->UnitSelection(SelectedUnits, ActorHit);
			}
		}
		else if (ActorHit->Tags.Contains("Building")) // Look for Actor Type.
		{
			if (!MultiselectCond) // Cannot MultiSelect Buildings.
			{
				if (!SelectedUnits.IsEmpty()) // Clears Selection to process new Array Selection.
				{
					SelectionInterface->NotHit(SelectedUnits);
				}

				if (SelectedBuilding.IsEmpty())
				{
					SelectionInterface->BuildingArrayIsEmpty(SelectedBuilding, ActorHit);
				}
				else if (SelectedBuilding.Num() > 0)
				{
					// return element
					SelectionInterface->ChangeElementInArray(SelectedBuilding, ActorHit);

					EBuildingTypes CurrentBuilding = SelectionInterface->GetBuildingType(ActorHit);

					if (CurrentBuilding == EBuildingTypes::Barracks)
					{
						CloseMarketplaceUI.Broadcast(true);
					}
					else if (CurrentBuilding == EBuildingTypes::Trader)
					{
						CloseBarracksUI.Broadcast(true);
					}
				}
			}
		}
		else
		{
			bNotHit = true;
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
				SelectionInterface->MultiUnitSelection(SelectedUnits, BaseAI);
			}
		}
	}
}


void AUserController::UpdateResources()
{
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
						if (!SelectedActor->ActorHasTag(FName("Building")) && !SelectedActor->ActorHasTag(
							FName("Resource")))
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

void AUserController::EnterPatrolMode()
{
	// Check if any units are selected.
	if (SelectedUnits.Num() > 0)
	{
		// if so, obtain which ones can patrol.
		PatrolUnits = SelectionInterface->ProccessPatrolMode(SelectedUnits);

		if (PatrolUnits.Num() > 0)
		{
			bPatrolMode = true;

			// Clear out old patrol points.
			PatrolPoints.Empty();
		}
	}
}

void AUserController::ProcessPatrolClick(FHitResult HitResult)
{
	if (bPatrolMode)
	{
		PatrolPoints.AddUnique(HitResult.Location);


		// If we click outside the specified amount of patrol points we just move on to the new location.
		if (PatrolPoints.Num() > 2)
		{
			PatrolPoints.Empty();
			bPatrolMode = false;
			SelectionInterface->MoveGroupToLocation(SelectedUnits, HitResult.Location);
		}

		// If we have two points selected.
		if (PatrolPoints.Num() == 2)
		{
			// Obtain the patrol units and set the patrol points.
			for (AGenericBaseAI* Unit : PatrolUnits)
			{
				for (int32 i = 0; i < PatrolUnits.Num(); ++i)
				{
					AGenericController* GenController = Cast<AGenericController>(PatrolUnits[i]->GetController());
					GenController->PatrolUnits = PatrolUnits;
					Unit->SetPatrolPoints(PatrolPoints[0], PatrolPoints[1]);
				}
			}
		}
	}
}
