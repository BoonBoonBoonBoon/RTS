// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/CombatInterface.h"

#include "AIContent/GenericBaseAI/GenericBaseAI.h"


void ICombatInterface::CustomTick(float DeltaTime)
{
	
}

// Add default functionality here for any ICombatInterface functions that are not pure virtual.
void ICombatInterface::MoveToEnemy(AActor* EnemyActor, TArray<AActor*> FriendlyActors)
{

	// TODO : Look up how i did stuff like this previously. I think its in either User controller or GenericAi.
	
	for (int i = 0; i < FriendlyActors.Num(); i++)
	{
		for (AActor* Actor : FriendlyActors)
		{
			AGenericBaseAI* AI = Cast<AGenericBaseAI>(Actor);
		}
	}
		//FVector EnemyLocation = EnemyActor->GetActorLocation();
		//TArray<FVector> FormationPositionsA = AI->CalculateGridFormationPositions();
}

bool ICombatInterface::FoundEnemyLocation()
{
	return {};
}
