// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/GenericController.h"


void AGenericController::MovePawn()
{
	if(CheckValid)
	{
		MoveToLocation(MoveLoc);
		CheckValid = false;
	}
}

void AGenericController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CheckValid)
	{
		MovePawn();
	}
	
	//MoveTo(*DestLoc);
}

AGenericController::AGenericController(FObjectInitializer const& ObjectInitializer)
{
}

void AGenericController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AGenericController::BeginPlay()
{
	Super::BeginPlay();
}

void AGenericController::SetupPer()
{
}

void AGenericController::MoveToDes(FVector& Destination)
{
	
		// Print the hit location coordinates to the output log
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: X=%f, Y=%f, Z=%f"), Destination.X, Destination.Y, Destination.Z);

	//UE_LOG(LogTemp, Warning, TEXT("Controller Address %p"), &Destination);
		//MoveToLocation(Destination);
}