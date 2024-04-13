// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/GenericController.h"

#include "AIContent/GenericBaseAI/GenericBaseAI.h"


void AGenericController::MovePawn()
{
	if(CheckValid)
	{
		MoveToLocation(MoveLoc);
		CheckValid = false;
	}
}

void AGenericController::PatrolLoc()
{
    if (bIsPatrolling)
    {
        // Get the current AI of the controller.
        AGenericBaseAI* AI = Cast<AGenericBaseAI>(GetPawn());

        if(FirstMove)
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
            float distA = FVector::Dist(GetPawn()->GetActorLocation(), PatrolPointA);

            if (distA < 220.0f)
            {
                // Calculate grid formation positions for the second patrol point.
                TArray<FVector> FormationPositionsB = AI->CalculateGridFormationPositions(PatrolPointB, PatrolUnits.Num());

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
        else
        {
            float distB = FVector::Dist(GetPawn()->GetActorLocation(), PatrolPointB);

            if (distB < 220.0f)
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
                bIsAtPointA = true;
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

void AGenericController::SetupPer()
{
}

void AGenericController::MoveToDes(FVector& Destination)
{
	
		// Print the hit location coordinates to the output log
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: X=%f, Y=%f, Z=%f"), Destination.X, Destination.Y, Destination.Z);

	//UE_LOG(LogTemp, Warning, TEXT("Controller Address %p"), &Destination);
		//MoveToLocation(Destination);
}



	/*if (bIsPatrolling)
	{
		// Get the current ai of the controller // Not Sure what im doing with this just yet.
		AGenericBaseAI* AI = Cast<AGenericBaseAI>(GetPawn());
		
		
		if(FirstMove)
		{
			// Calculate grid formation positions for the first patrol point
			TArray<FVector> FormationPositionsA = AI->CalculateGridFormationPositions(PatrolPointA, PatrolUnits.Num());
			// Move each unit to its position in the grid formation
			for (int i = 0; i < PatrolUnits.Num(); i++)
			{
				// Get the AI controller of the unit
				if (AAIController* AIController = Cast<AAIController>(PatrolUnits[i]->GetController()))
				{
					AIController->MoveToLocation(FormationPositionsA[i]);
				}
			}
			FirstMove = false;

			/*UE_LOG(LogTemp, Warning, TEXT("FirstMove"));
			MoveToLocation(PatrolPointA);
			FirstMove = false;#1#
		}


		float distA = FVector::Dist(GetPawn()->GetActorLocation(), PatrolPointA);
		float distB = FVector::Dist(GetPawn()->GetActorLocation(), PatrolPointB);
		UE_LOG(LogTemp, Warning, TEXT("Distance to A: %f, Distance to B: %f"), distA, distB);


		if (distA < 110.0f)
		{
			// Calculate grid formation positions for the second patrol point
			TArray<FVector> FormationPositionsB = AI->CalculateGridFormationPositions(PatrolPointB, PatrolUnits.Num());

			// Move each unit to its position in the grid formation
			for (int i = 0; i < PatrolUnits.Num(); i++)
			{
				// Get the AI controller of the unit
				if (AAIController* AIController = Cast<AAIController>(PatrolUnits[i]->GetController()))
				{
					AIController->MoveToLocation(FormationPositionsB[i]);
				}
			}
		//	MoveToLocation(PatrolPointB);
			//UE_LOG(LogTemp, Warning, TEXT("PatrolPointB Location: X=%f, Y=%f, Z=%f"), PatrolPointB.X, PatrolPointB.Y, PatrolPointB.Z);
		}
		else if (distB < 110.0f)
		{
			// Calculate grid formation positions for the first patrol point
			TArray<FVector> FormationPositionsA = AI->CalculateGridFormationPositions(PatrolPointA, PatrolUnits.Num());

			// Move each unit to its position in the grid formation
			for (int i = 0; i < PatrolUnits.Num(); i++)
			{
				// Get the AI controller of the unit
				if (AAIController* AIController = Cast<AAIController>(PatrolUnits[i]->GetController()))
				{
					AIController->MoveToLocation(FormationPositionsA[i]);
				}
			}
		//	MoveToLocation(PatrolPointA);
			//UE_LOG(LogTemp, Warning, TEXT("PatrolPointA Location: X=%f, Y=%f, Z=%f"), PatrolPointA.X, PatrolPointA.Y, PatrolPointA.Z);
		}
	}*/