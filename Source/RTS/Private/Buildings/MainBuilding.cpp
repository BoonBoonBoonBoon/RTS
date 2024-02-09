// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/MainBuilding.h"

// Sets default values
AMainBuilding::AMainBuilding()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainBuilding::BeginPlay()
{
	Super::BeginPlay();
	
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

