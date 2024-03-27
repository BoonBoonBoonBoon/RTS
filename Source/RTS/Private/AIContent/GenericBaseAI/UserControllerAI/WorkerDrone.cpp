// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"

AWorkerDrone::AWorkerDrone()
{
	WorkerAttributesComponent = CreateDefaultSubobject<UWorkerAttributesComponent>(TEXT("AttributesComponent"));
	
	// Identify the Worker Drone.
	Tags.Add("WorkerDrone");
}
