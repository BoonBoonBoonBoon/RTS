// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/CombatInterface.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"

 /*	Todo : W/O Perception Currently. 
  *	The Friendly AI that can attack must find an actor that they can attack. 
  *	They do this when the player clicks on the Enemy AI target in usercontroller event key.
  *	Once we find the ai target the friendly AI must be constantly updated about where the enemy ai is currently at in the combatinterface,
  *	we can do this by checking if we have found an enemy and in the combattick function check if the boolean is true.
  *	if its true the enemy will constantly move to the currently found enemy ai.
  *	to do this we then must make a function where the friendly ai that have the Attack attribute will find the closest location to the enemy ai.
  *	this location must not be no further than 150 units away from the enemy ai.
  *	furthermore, the friendly ai must ignore the exact and nearby locations of the friendly ai that are also attacking the enemy ai, this should be no more than 40 units.
  *	Once these conditions are met the friendly ai will move to the location and attack the enemy ai.
  *	if we also then have new incoming friendlies after the initial attack, they will also move to the enemy ai and attack and find themselves a location to attack from.
  * 
  * 
  */



// We want to make it so when the enemy ai comes into view of the friendly ai the friendly ai will either move to the first ai its seen or the closest ai to it.
// if that ai then has 3 or more attacking it, the friendly ai will move to the next closest ai to it.

// todo Look at docs 

void ICombatInterface::CombatTick(float DeltaTime)
{
	if(EnemyFound)
	{
		//UpdateEnemyLocation();

		/*for (AActor* FriendlyActor : /* all friendly AIs with the Attack attribute #1#)
		{
			AttackLocation = FindAttackLocation(AttackingUnits);
			MoveToAttackLocation(AttackingUnits, AttackLocation);
		}*/
	}
}

// 1. First Call from event key in usercontroller
void ICombatInterface::FindEnemy(AActor* EnemyActor, TArray<AActor*> FriendlyActors)
{
	// Find all friendly actors that can attack.
	AttackingUnits = ProccessAttackMode(FriendlyActors);
	
	if (AttackingUnits.Num() > 0)
	{
		for(int32 i = 0; i < AttackingUnits.Num(); ++i)
		{
			if (AGenericController* AIController = Cast<AGenericController>(AttackingUnits[i]->GetController()))
			{
				//AIController->MoveToLocation(SurroundingPositions[i]);
			}
		}
	}
	
	CurrentEnemy = EnemyActor;
	EnemyFound = true;
}



TArray<AGenericBaseAI*> ICombatInterface::ProccessAttackMode(TArray<AActor*> Units)
{
	TArray<AGenericBaseAI*> UnitsCanAttack;

	for (AActor* Src : Units)
	{
		if (auto GenActor = Cast<AGenericBaseAI>(Src))
		{
			if(GenActor->UnitDataMap.Contains(GenActor->UnitType))
			{
				if(TArray<EUnitAttributes> Att = GenActor->UnitDataMap[GenActor->UnitType].Attributes; Att.Contains(EUnitAttributes::Attack))
				{
					UnitsCanAttack.AddUnique(GenActor);
				}
			}
		}
	}
	return UnitsCanAttack;
}


/*
TArray<FVector> ICombatInterface::UpdateEnemyLocation()
{
	if(CurrentEnemy)
	{
		FVector EnemyLocation = CurrentEnemy->GetActorLocation();
	}
}
*/


/*
FVector ICombatInterface::FindAttackLocation(AGenericBaseAI* FriendlyActor)
{
	FVector ClosestLocation;
	float MinDis = FLT_MAX;
	
	// Iterate over all locations within 150 units of the enemy
	for(FVector Location : /* all locations within 150 units of the enemy #1#)
	{
		// Check if the location is within 40 units of any other friendly actor.
		if (!IsLocationOccupied(Location, /* all other friendly AIs #1#, 40.0f))
		{
			float Distance = FVector::Dist(Location, FriendlyActor->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestLocation = Location;
			}
		}
	}
	return ClosestLocation;
}*/

/*
void ICombatInterface::MoveToAttackLocation(AGenericBaseAI* FriendlyActor, FVector AttackLocation)
{
	if(AGenericController* AIController = Cast<AGenericController>(FriendlyActor->GetController()))
	{
		AIController->MoveToLocation(AttackLocation);
	}
}
*/


///////////////




/*
TArray<FVector> ICombatInterface::CalculateSurroundingPositions(FVector EnemyLocation, int32 UnitsCount, float Radius)
{
    TArray<FVector> Positions;
    float AngleStep = 360.0f / UnitsCount;

    for (int32 i = 0; i < UnitsCount; ++i)
    {
        float AngleRadians = FMath::DegreesToRadians(AngleStep * i);
        Positions.Add(EnemyLocation + Radius * FVector(FMath::Cos(AngleRadians), FMath::Sin(AngleRadians), 0.0f));
    }

    return Positions;
}


void ICombatInterface::MoveToEnemy(AActor* EnemyActor, TArray<AActor*> FriendlyActors)
{
	//	TODO :  Marquee tool is adding loads of random actors???
	
    if (FriendlyActors.Num() > 0)
    {
        AttackingUnits = ProccessAttackMode(FriendlyActors);
        SurroundingPositions = CalculateSurroundingPositions(EnemyActor->GetActorLocation(), FriendlyActors.Num(), 300.0f);

        if (AttackingUnits.Num() > 0)
        {
            for(int32 i = 0; i < AttackingUnits.Num(); ++i)
            {
                if (AAIController* AIController = Cast<AAIController>(AttackingUnits[i]->GetController()))
                {
                    AIController->MoveToLocation(SurroundingPositions[i]);
                }
            }
        }
    }
}

TArray<AGenericBaseAI*> ICombatInterface::ProccessAttackMode(TArray<AActor*> Units)
{
    TArray<AGenericBaseAI*> UnitsCanAttack;

    for (AActor* Src : Units)
    {
        if (auto GenActor = Cast<AGenericBaseAI>(Src))
        {
            if(GenActor->UnitDataMap.Contains(GenActor->UnitType))
            {
                if(TArray<EUnitAttributes> Att = GenActor->UnitDataMap[GenActor->UnitType].Attributes; Att.Contains(EUnitAttributes::Attack))
                {
                    UnitsCanAttack.AddUnique(GenActor);
                }
            }
        }
    }
    return UnitsCanAttack;
}
*/


/////////////////////////////

/*
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
*/

