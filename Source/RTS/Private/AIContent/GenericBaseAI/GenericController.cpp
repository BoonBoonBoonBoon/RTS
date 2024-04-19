// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/GenericController.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Perception/AIPerceptionComponent.h"



void AGenericController::MovePawn()
{
	if(CheckValid)
	{
		MoveToLocation(MoveLoc);
		CheckValid = false;
	}
}

/**
 * @brief Handles the patrol logic for the AI controller.
 *
 * This function is responsible for managing the patrol behavior of the AI controller.
 * If the AI is set to patrol, it will move between two points (PatrolPointA and PatrolPointB) in a grid formation.
 * The function first checks if this is the first move, and if so, calculates the grid formation positions for the first patrol point and moves each unit to its position.
 * Then, it checks if the units are at the first patrol point. If they are, it calculates the grid formation positions for the second patrol point and moves each unit to its position.
 * If the units are not at the first patrol point, it assumes they are at the second patrol point, calculates the grid formation positions for the first patrol point, and moves each unit back to its position.
 * The function uses a distance check to determine when the units have reached a patrol point and should move to the next one.
 */
void AGenericController::PatrolLoc()
{
	if (bIsPatrolling)
	{
		// Get the current AI of the controller.
		AGenericBaseAI* AI = Cast<AGenericBaseAI>(GetPawn());

		if (FirstMove)
		{
			// Calculate grid formation positions for the first patrol point.
			TArray<FVector> FormationPositionsA = AI->CalculateGridFormationPositions(PatrolPointA, PatrolUnits.Num());

			// Move each unit to its position in the grid formation.
			for (int i = 0; i < PatrolUnits.Num(); i++)
			{
				// Get the AI controller of the unit.
				if (AAIController* AIController = Cast<AAIController>(PatrolUnits[i]->GetController()))
				{
					AIController->MoveToLocation(FormationPositionsA[i]);
				}
			}
			FirstMove = false;
			bIsAtPointA = true;
		}

		if (bIsAtPointA)
		{
			for (AGenericBaseAI* Unit : PatrolUnits)
			{
				float distA = FVector::Dist(Unit->GetActorLocation(), PatrolPointA);

				if (distA < 300.0f)
				{
					// Calculate grid formation positions for the second patrol point.
					TArray<FVector> FormationPositionsB = AI->CalculateGridFormationPositions(
						PatrolPointB, PatrolUnits.Num());

					// Move each unit to its position in the grid formation.
					for (int i = 0; i < PatrolUnits.Num(); i++)
					{
						// Get the AI controller of the unit.
						if (AAIController* AIController = Cast<AAIController>(PatrolUnits[i]->GetController()))
						{
							AIController->MoveToLocation(FormationPositionsB[i]);
						}
					}
					bIsAtPointA = false;
				}
			}
		}
		else
		{
			//float distB = FVector::Dist(GetPawn()->GetActorLocation(), PatrolPointB);
			for (AGenericBaseAI* Unit : PatrolUnits)
			{
				float distB = FVector::Dist(Unit->GetActorLocation(), PatrolPointB);

				if (distB < 300.0f)
				{
					// Calculate grid formation positions for the first patrol point.
					TArray<FVector> FormationPositionsA = AI->CalculateGridFormationPositions(
						PatrolPointA, PatrolUnits.Num());

					// Move each unit to its position in the grid formation.
					for (int i = 0; i < PatrolUnits.Num(); i++)
					{
						// Get the AI controller of the unit.
						if (AAIController* AIController = Cast<AAIController>(PatrolUnits[i]->GetController()))
						{
							AIController->MoveToLocation(FormationPositionsA[i]);
						}
					}
					bIsAtPointA = true;
				}
			}
		}
	}
}


void AGenericController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CheckValid)
	{
		MovePawn();
	}

	if (bIsPatrolling)
	{
		PatrolLoc();
	}
	
}

AGenericController::AGenericController(FObjectInitializer const& ObjectInitializer)
{
}

void AGenericController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AGenericController::BeginPlay()
{
	Super::BeginPlay();
}



