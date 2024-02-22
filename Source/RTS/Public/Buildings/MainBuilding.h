
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/BuildingInterface.h"
#include "MainBuilding.generated.h"

class UDecalComponent;
class UBoxComponent;

UCLASS()
class RTS_API AMainBuilding : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainBuilding();

	// Spawns the selected units into the current world.
	//void SpawnUnits();

	
	UPROPERTY(EditAnywhere)
	UDecalComponent* SelectedDecalComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Building Type")
	EBuildingTypes BuildingType;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
