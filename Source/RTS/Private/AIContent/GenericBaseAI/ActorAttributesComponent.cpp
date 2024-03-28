// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/ActorAttributesComponent.h"

// Sets default values for this component's properties
UActorAttributesComponent::UActorAttributesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Gather is not valid by default.
	bCanGather = false;
}


// Called when the game starts
void UActorAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActorAttributesComponent::SetCanGather(bool bNewCanGather)
{
	//bCanGather = bNewCanGather;
	//UE_LOG(LogTemp, Warning, TEXT("Bool is: %s"), bCanGather ? TEXT("true") : TEXT("false"));
}

bool UActorAttributesComponent::CanGather() const
{
	return {};
}

