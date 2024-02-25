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

EBuildingTypes AMainBuilding::AssignBuildingType(const APawn* Building)
{
	if (const AMainBuilding* MainBuilding = Cast<AMainBuilding>(Building))
	{
		return EBuildingTypes::Invalid;
	}
	else if (const ABarracksBuilding* Barracks = Cast<ABarracksBuilding>(Building))
	{
		return EBuildingTypes::Barracks;
	}
	else if (const AMarketplaceBuilding* Marketplace = Cast<AMarketplaceBuilding>(Building))
	{
		return EBuildingTypes::Trader;
	}

	return EBuildingTypes::Invalid;
}

void AMainBuilding::AssignChildrenBuildingTypes(const AMainBuilding* MainBuilding)
{
	TArray<AActor*> Children;
	MainBuilding->GetAttachedActors(Children);

	for (AActor* Child : Children)
	{
		if (const AMarketplaceBuilding* MarketplaceChild = Cast<AMarketplaceBuilding>(Child))
		{
			EBuildingTypes BuildingType = AssignBuildingType(MarketplaceChild);
			// Additional logic for Marketplace child
			/*if(static_cast<bool>(BuildingType))
			{

			Give the building the Tag (Barracks since this is impossible to setup idk how to access enums)

			// Loook up How to set a Pawn class to a specific enum and retrive that data?
			////and then set the tag to that enum
				
			}*/
			
		}
		else if (const ABarracksBuilding* BarracksChild = Cast<ABarracksBuilding>(Child))
		{
			EBuildingTypes BuildingType = AssignBuildingType(BarracksChild);
			// Additional logic for Barracks child

			
		}
	}
}

/*void AMainBuilding::SpawnUnits()
{
}*/

// Called when the game starts or when spawned
void AMainBuilding::BeginPlay()
{
	Super::BeginPlay();


	AssignBuildingType(this);
	AssignChildrenBuildingTypes(this);
	UE_LOG(LogTemp, Warning, TEXT("Building tag added to %s"), *GetName());
	
	
	/*if (UChildActorComponent* ChildActor = FindComponentByClass<UChildActorComponent>())
	{
		/*for(const APawn* Building : ChildActor)
		{
			//BuildingType = IBuildingInterface::GetBuildingType(Building);
		//	BuildingType = IBuildingInterface::AssignBuildingType(Building);
			
			BuildInt->AssignBuildingType(Building);
			#1#
		//}
	}*/
}
	
// EBuildingTypes BuildingType =IBuildingInterface::GetBuildingType(this);

	

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

