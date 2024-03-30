// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/Heavy/Siege/BasicSiege.h"

ABasicSiege::ABasicSiege()
{

	BasicScoutAttributesComponent = CreateDefaultSubobject<UBasicScoutAttributesComponent>(TEXT("AttributesComponent"));

	Tags.Add("BasicSiege");
}
