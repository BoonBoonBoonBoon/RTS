// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/GenericBaseAIController.h"

AGenericBaseAIController::AGenericBaseAIController()
{
	BBComp = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard");	
	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComp"));
}

void AGenericBaseAIController::BeginPlay()
{
	// If the behaviour tree is valid
	if (IsValid(BT.Get()))
	{
		if(IsValid(BTComp))
		{
			// Run behaviour tree.
			RunBehaviorTree(BT.Get());

			// Then Run the BTComponent using the BT Asset.
			BTComp->StartTree(*BT.Get());
		}
	}
}

void AGenericBaseAIController::OnPossess(APawn* InPawn)
{
	// Need to initialize the BT & BB.
	// Check if Behaviour Tree is valid.
	if(IsValid(BT.Get()))
	{
		// Check is BlackBoard comp is valid.
		if(IsValid(Blackboard.Get()))
		{
			// boolean that checks if blackboard is initilaized.
			// Get the blackboard asset for the Behaviour Tree. 
			Blackboard->InitializeBlackboard((*BT.Get()->BlackboardAsset));
		}
	}
}

void AGenericBaseAIController::MoveToDest(const FVector& Destination)
{
	AAIController* aiController = Cast<AAIController>(this);
	if(aiController)
	{
		aiController->MoveToLocation(Destination);
	}
}
