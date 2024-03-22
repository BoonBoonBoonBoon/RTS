// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/UnitInterface.h"

#include "AIContent/GenericBaseAI/UserControllerAI/Light/Infantry/lightInfantry.h"

// Add default functionality here for any IUnitInterface functions that are not pure virtual.
bool IUnitInterface::IsUnitSelected(const TArray<AActor*>& UnitArray, const AActor* UnitToCheck)
{
	return UnitArray.Contains(UnitToCheck);
}

EUnitTypes IUnitInterface::GetUnitType(const AActor* UnitActor)
{
	{
		if(UnitActor)
		{
			if(const AWorkerDrone* WorkerDrone = Cast<AWorkerDrone>(UnitActor))
			{
				AssignUnitType(WorkerDrone);
				return EUnitTypes::Worker;
			}
			else
			{
				return EUnitTypes::Invalid;
			}
		}
		return EUnitTypes::Invalid;
	}
}

EUnitTypes IUnitInterface::AssignUnitType(const AActor* UnitActor)
{
	if(UnitActor)
	{
		if(Cast<AWorkerDrone>(UnitActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Unit type assigned: Worker"));
			return EUnitTypes::Worker;
		} else if (Cast<AlightInfantry>(UnitActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Unit type assigned: Light Infantry"));
			return EUnitTypes::LightInfantry;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Unit type assigned: Invalid"));
	return EUnitTypes::Invalid;
}
