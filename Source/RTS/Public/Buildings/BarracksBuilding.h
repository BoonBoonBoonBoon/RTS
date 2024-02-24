// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/MainBuilding.h"
#include "BarracksBuilding.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ABarracksBuilding : public AMainBuilding
{
	GENERATED_BODY()

public:
	ABarracksBuilding();

	//void SpawnUnit();
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Building Type")
	EBuildingTypes Type;*/
};
