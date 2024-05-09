
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingController.h"
#include "GameFramework/Actor.h"
#include "Interfaces/SelectionInterface.h"
#include "MainBuilding.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOpenBarracksUIEvent, bool, bOpenBarracksUI, bool, bOpenMarketPlaceUI);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOpenMarketPlaceUIEvent, bool, bOpenMarketPlaceUI, bool, bOpenBarracksUI);

class UDecalComponent;
class UBoxComponent;

UCLASS()
class RTS_API AMainBuilding : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainBuilding();

	UPROPERTY(EditAnywhere)
	ABuildingController* BuildingController;

	ISelectionInterface* SelectionInterface;
	
	UPROPERTY(EditAnywhere)
	UDecalComponent* SelectedDecalComp;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;


	// ------------------- Widgets -------------------

	UPROPERTY(BlueprintAssignable)
	FOpenBarracksUIEvent OpenBarracksUI;

	UPROPERTY(BlueprintAssignable)
	FOpenMarketPlaceUIEvent OpenMarketPlaceUI;
	
	void OpenBarracksUIEvent();
	void OpenMarketUIEvent();
	
	// ---------------------------------
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
