// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/BTTask_MoveToLocationPathfinding.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MoveToLocationPathfinding::UBTTask_MoveToLocationPathfinding()
{
	// Gives node name, What we see on bp node
	NodeName = "Move To Location";

	// Accept only vectors, since the blackboard key only takes vectors as a data type
	// This says that is filters only for vectors and nothing else for the task * IE. SetValueVector
	//BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindRandomLocation, BlackboardKey));
	
}

FString UBTTask_MoveToLocationPathfinding::GetStaticDescription() const
{
	return Super::GetStaticDescription();
	
	//return FString::Printf(TEXT("Vector %s"), *BlackboardKey.SelectedKeyName.ToString());
}

EBTNodeResult::Type UBTTask_MoveToLocationPathfinding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Empty initializer 
	FNavLocation Location{};

	// Get the AI pawn. Grab the AI controller of the owner component.
	if (AAIController* AiController = OwnerComp.GetAIOwner())
	{/*
		const APawn* AIPawn = AiController->GetPawn();
		// Get Pawn Origin
		const FVector Origin = AIPawn->GetActorLocation();

		// Check if the Blackboard component is valid
		if (UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
		{
			// Get the vector key name used in Blackboard
			FName VectorKeyName = (TEXT("HitLocationKey"));

			// Check if the key is valid and holds a vector value
			if (BlackboardComp->IsVectorValueSet(VectorKeyName))
			{
				// Get the vector value from the Blackboard
				FVector TargetLocation = BlackboardComp->GetValueAsVector(VectorKeyName);

				// Set the location for navigation
				Location.Location = TargetLocation;

				// Obtain the navigation system and find a random location
				const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
				if (IsValid(NavSystem) && NavSystem->
					FindPathToLocationSynchronously(GetWorld(), Origin, TargetLocation))
				{
					// The navigation system found a path to the target location.
					// You might want to add logic here for handling the successful pathfinding.
					// For example, you could call MoveToLocation or perform other actions.

					// Move the AI to the target location
					AiController->MoveToLocation(TargetLocation);

					return EBTNodeResult::Succeeded;
				}
			}
		}*/
	}
	return EBTNodeResult::Failed;
}
