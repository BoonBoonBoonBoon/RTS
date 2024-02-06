// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/WayPointActor.h"

// Sets default values
AWayPointActor::AWayPointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AWayPointActor::SpawnActorLocation(const FVector& SpawnLocation)
{
	// Define the spawn parameters
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawn the actor at the specified location
	AActor* NewActor = GetWorld()->SpawnActor<AActor>(AWayPointActor::StaticClass(), SpawnLocation, GetActorRotation(), SpawnParams);
	if(NewActor)
	{
		
	}
}

// Called when the game starts or when spawned
void AWayPointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWayPointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

