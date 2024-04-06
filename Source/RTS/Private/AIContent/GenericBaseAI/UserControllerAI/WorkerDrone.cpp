// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"

AWorkerDrone::AWorkerDrone()
{

	// Obtain the Unit Type we are working with.
	EUnitTypes CurrentUnit = EUnitTypes::Worker;

	// Get the Unit Data for the Current Unit.
	UnitData = ISelectionInterface::GetUnitDataForUnit(CurrentUnit);

	// Pass the Data back some how 
		
	WorkerAttributesComponent = CreateDefaultSubobject<UWorkerAttributesComponent>(TEXT("AttributesComponent"));
	
	// Identify the Worker Drone.
	Tags.Add("WorkerDrone");
}
