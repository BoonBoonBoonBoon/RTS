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


void AGenericController::PatrolLoc()
{
	if (bIsPatrolling)
	{
		
		if(FirstMove)
		{
			UE_LOG(LogTemp, Warning, TEXT("FirstMove"));
			MoveToLocation(PatrolPointA);
			FirstMove = false;
		}


		float distA = FVector::Dist(GetPawn()->GetActorLocation(), PatrolPointA);
		float distB = FVector::Dist(GetPawn()->GetActorLocation(), PatrolPointB);
		UE_LOG(LogTemp, Warning, TEXT("Distance to A: %f, Distance to B: %f"), distA, distB);


		if (distA < 110.0f)
		{
			MoveToLocation(PatrolPointB);
			UE_LOG(LogTemp, Warning, TEXT("PatrolPointB Location: X=%f, Y=%f, Z=%f"), PatrolPointB.X, PatrolPointB.Y, PatrolPointB.Z);
		}
		else if (distB < 110.0f)
		{
			MoveToLocation(PatrolPointA);
			UE_LOG(LogTemp, Warning, TEXT("PatrolPointA Location: X=%f, Y=%f, Z=%f"), PatrolPointA.X, PatrolPointA.Y, PatrolPointA.Z);
		}

		
		/*if (FVector::Dist(GetPawn()->GetActorLocation(), PatrolPointA) < 50.0f)
		{
			MoveToLocation(PatrolPointB);
			UE_LOG(LogTemp, Warning, TEXT("PatrolPointB Location: X=%f, Y=%f, Z=%f"), PatrolPointB.X, PatrolPointB.Y, PatrolPointB.Z);
		}
		else if (FVector::Dist(GetPawn()->GetActorLocation(), PatrolPointB) < 50.0f)
		{
			MoveToLocation(PatrolPointA);
			UE_LOG(LogTemp, Warning, TEXT("PatrolPointA Location: X=%f, Y=%f, Z=%f"), PatrolPointA.X, PatrolPointA.Y, PatrolPointA.Z);
		}*/
	}
}

void AGenericController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CheckValid)
	{
		MovePawn();
	}

	if (bIsPatrolling)
	{
		PatrolLoc();
	}
	
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
