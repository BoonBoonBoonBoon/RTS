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

	UE_LOG(LogTemp, Warning, TEXT("Found Enemy"));


	//	TODO :  Marquee tool is adding loads of random actors??? 
	// If we have units available 
	if (FriendlyActors.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Number of FriendlyActors units: %d"), FriendlyActors.Num());

		AttackingUnits = ProccessAttackMode(FriendlyActors);

		// if so, obtain which ones can patrol.
		if (AttackingUnits.Num() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Number of attacking units: %d"), AttackingUnits.Num());
		}

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

