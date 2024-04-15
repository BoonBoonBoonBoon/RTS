// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/CombatInterface.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"


TArray<FVector> ICombatInterface::CalculateSurroundingPositions(FVector EnemyLocation, int32 UnitsCount, float Radius)
{
	TArray<FVector> Positions; // Array to store the calculated positions

	float AngleStep = 360.0f / UnitsCount; // Calculate the angle step

	// iterate through each unit
	for (int32 i = 0; i < UnitsCount; ++i)
	{
		float AngleDegrees = AngleStep * i; // Calculate the angle for the current unit
		float AngleRadians = FMath::DegreesToRadians(AngleDegrees); // Convert the angle to radians

		FVector Position = EnemyLocation + Radius * FVector(FMath::Cos(AngleRadians), FMath::Sin(AngleRadians), 0.0f);
		Positions.Add(Position);
	}

	return Positions;
}

void ICombatInterface::CustomTick(float DeltaTime)
{
}

// Add default functionality here for any ICombatInterface functions that are not pure virtual.

void ICombatInterface::MoveToEnemy(AActor* EnemyActor, TArray<AActor*> FriendlyActors)
{
	// TODO : Look up how i did stuff like this previously. I think its in either User controller or GenericAi.
	
	//	TODO :  Marquee tool is adding loads of random actors???
	
	// If we have units available 
	if (FriendlyActors.Num() > 0)
	{
		AttackingUnits = ProccessAttackMode(FriendlyActors);

		 TArray<FVector> SurroundingPositions = CalculateSurroundingPositions(EnemyActor->GetActorLocation(), FriendlyActors.Num(), 300.0f);
		
		// if so, obtain which ones can patrol.
		if (AttackingUnits.Num() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Number of attacking units: %d"), AttackingUnits.Num());

			for(int32 i = 0; i < AttackingUnits.Num(); ++i)
			{
				// Get the AI controller of the unit.
				if (AAIController* AIController = Cast<AAIController>(AttackingUnits[i]->GetController()))
				{
					// Move the unit to the surrounding position.
					AIController->MoveToLocation(SurroundingPositions[i]);
				}
			}
			
			//SurroundEnemy(EnemyActor, AttackingUnits);
			
			// Log name of each unit attacking 
			for (AGenericBaseAI* Unit : AttackingUnits)
			{
				if (Unit)
				{
					FString UnitName = Unit->GetName();
					UE_LOG(LogTemp, Warning, TEXT("Unit Name: %s"), *UnitName);
				}
			}
		}
	}
}

void ICombatInterface::SurroundEnemy(AActor* EnemyActor, TArray<AGenericBaseAI*> FriendlyActors)
{
	// Get the enemy's location.
	FVector EnemyLocation = EnemyActor->GetActorLocation();
	
	// Calculate the number of units.
	int32 UnitsCount = FriendlyActors.Num();

	// Calculate the angle between each point (in radians).
	float AngleStep = 2 * PI / UnitsCount;

	// Array to store the target positions for each unit.
	TArray<FVector> TargetPositions;
	
	// Calculate the target positions.
	for (int32 i = 0; i < UnitsCount; ++i)
	{
		FVector SurroundRadius = FriendlyActors[i]->GetActorLocation();
		
		// Calculate the angle for this point.
		float Angle = i * AngleStep;

		// Calculate the position for this point.
		FVector Position = EnemyLocation + FVector(cos(Angle), sin(Angle), 0) * SurroundRadius;

		// Add the position to the array.
		TargetPositions.Add(Position);
	}

	// Assign each unit to a target position.
	for (int32 i = 0; i < UnitsCount; ++i)
	{
		AActor* Unit = FriendlyActors[i];
		FVector TargetPosition = TargetPositions[i];

		// Command the unit to move to the target position.
		// This assumes you have a method in your unit's class to command it to move to a position.
		if (AGenericBaseAI* AIUnit = Cast<AGenericBaseAI>(Unit))
		{
			AIUnit->GatherAroundEnemy(TargetPosition);
		}
	}
}



TArray<AGenericBaseAI*> ICombatInterface::ProccessAttackMode(TArray<AActor*> Units)
{
	// Temp Array to store the units that can attack.
	TArray<AGenericBaseAI*> UnitsCanAttack;

	// Search for actors that have Attack attribute.
	for (AActor* Src : Units)
	{
		if (auto GenActor = Cast<AGenericBaseAI>(Src))
		{
			if(GenActor->UnitDataMap.Contains(GenActor->UnitType))
			{
				// Obtain the Attributes of each Unit.
				if(TArray<EUnitAttributes> Att = GenActor->UnitDataMap[GenActor->UnitType].Attributes; Att.Contains(EUnitAttributes::Attack))
				{
					UnitsCanAttack.AddUnique(GenActor);
				}
			}
		}
	}
	return UnitsCanAttack;
}

