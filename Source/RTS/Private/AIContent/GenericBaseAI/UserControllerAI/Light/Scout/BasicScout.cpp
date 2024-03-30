// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/Light/Scout/BasicScout.h"

#include "ToolContextInterfaces.h"

ABasicScout::ABasicScout()
{
	ScoutAttributesComponent = CreateDefaultSubobject<UBasicScoutAttributesComponent>(TEXT("AttributesComponent"));
	
	Tags.Add("BasicScout");
}
