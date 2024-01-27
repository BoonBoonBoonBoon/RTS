// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/BTTask_MoveToLocationPathfinding.h"

#include "AIContent/GenericBaseAI/GenericBaseAIController.h"
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
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		FVector HitLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("HitLocationKey"));
		AIController->MoveToLocation(HitLocation);

		// Consider checking if the AI reached the destination and return success or failure accordingly.
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
	//return Super::ExecuteTask(OwnerComp, NodeMemory);
	
}
