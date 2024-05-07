
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingController.h"
#include "GameFramework/Actor.h"
#include "Interfaces/SelectionInterface.h"
#include "MainBuilding.generated.h"

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

	UFUNCTION(BlueprintImplementableEvent, Category = "BuildingWidget")
	void OpenMarketPlaceWidget();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "BuildingWidget")
	void OpenBarracksWidget();

	bool OpenMarket(bool bOpen);
	bool OpenBarracks(bool bOpen);
	void OpenBarracksUIEvent();

	// Open & Close Widgets ------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	bool bOpenMarketPlace = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	bool bOpenBarracks = false;

	// ---------------------------------
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
