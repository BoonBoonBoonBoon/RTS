// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/Light/Infantry/lightInfantry.h"
#include "AIContent/GenericBaseAI/ActorAttributesComponent.h"

AlightInfantry::AlightInfantry()
{

	EUnitTypes CurrentUnit = EUnitTypes::LightInfantry;
	
	ActorAttributesComponent = CreateDefaultSubobject<ULightInfantryAttributesComponent>(TEXT("AttributesComponent"));
	
	// Identify the Worker Drone.
	Tags.Add("LightInfantry");
}
