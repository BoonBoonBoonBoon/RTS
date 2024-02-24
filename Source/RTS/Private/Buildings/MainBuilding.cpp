// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/MainBuilding.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Interfaces/BuildingInterface.h"


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

/*void AMainBuilding::SpawnUnits()
{
}*/

// Called when the game starts or when spawned
void AMainBuilding::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Building tag added to %s"), *GetName());
	
	// EBuildingTypes BuildingType =IBuildingInterface::GetBuildingType(this);

	
	/*if (UChildActorComponent* ChildActor = FindComponentByClass<UChildActorComponent>())
	{
		if (ABarracksBuilding* BarracksBuilding = Cast<ABarracksBuilding>(ChildActor->GetChildActor()))
		{
			// The ChildActorComponent is of type ABarracksBuilding
			BarracksBuilding->BuildingType = EBuildingTypes::Barracks;
		}
		else if(AMarketplaceBuilding* MarketplaceBuilding = Cast<AMarketplaceBuilding>(ChildActor->GetChildActor()))
		{
			MarketplaceBuilding->BuildingType = EBuildingTypes::Trader;
		}
	}*/
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

