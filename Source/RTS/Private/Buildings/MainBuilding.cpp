// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/MainBuilding.h"
#include "Buildings/MarketplaceBuilding.h"
#include "Components/BoxComponent.h"



class AMarketplaceBuilding;
class ABarracksBuilding;

// Sets default values
AMainBuilding::AMainBuilding()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Collision");
	
	// Set Tag to building
	Tags.Add("Building");
}


void AMainBuilding::OpenBarracksUIEvent()
{
	OpenBarracksUI.Broadcast(true);
}

void AMainBuilding::OpenMarketUIEvent()
{
	OpenMarketPlaceUI.Broadcast(true);
}


// Called when the game starts or when spawned
void AMainBuilding::BeginPlay()
{
	Super::BeginPlay();
	// Cast this to ISelectionInterface
	SelectionInterface = Cast<ISelectionInterface>(this);

	SelectionInterface->AssignBuildingType(this);
}


// Called every frame
void AMainBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


