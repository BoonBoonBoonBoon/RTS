// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/MainBuilding.h"

#include "Buildings/BarracksBuilding.h"
#include "Buildings/MarketplaceBuilding.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Interfaces/BuildingInterface.h"


class AMarketplaceBuilding;
class ABarracksBuilding;
// Sets default values
AMainBuilding::AMainBuilding()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Collision");
	//BoxComponent->SetupAttachment(RootComponent);
	
	SelectedDecalComp = CreateDefaultSubobject<UDecalComponent>("Decal");
	SelectedDecalComp->SetupAttachment(BoxComponent);
	
	// Set Tag to building
	Tags.Add("Building");

	
}
 
// Called when the game starts or when spawned
void AMainBuilding::BeginPlay()
{
	Super::BeginPlay();

	// Shouldn't be visible at the start of the game.
	SelectedDecalComp->SetVisibility(false);
	
}


// Called every frame
void AMainBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainBuilding::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

