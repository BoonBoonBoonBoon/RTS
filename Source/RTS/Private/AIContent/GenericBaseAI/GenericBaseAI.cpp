// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "UserController.h"
#include "AIContent/GenericBaseAI/GenericController.h"
#include "Components/DecalComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

class AUserController; 

// Sets default values
AGenericBaseAI::AGenericBaseAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorAttributesComponent = CreateDefaultSubobject<UActorAttributesComponent>(TEXT("ActorAttributesComponent"));
	
	SelectedDecalComp = CreateDefaultSubobject<UDecalComponent>("Decal");
	SelectedDecalComp->SetupAttachment(RootComponent);
	
	// Set Tag to building
	Tags.Add("Unit");
	
}

void AGenericBaseAI::MyQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
}

void AGenericBaseAI::MovePTR()
{
	if(ValidHit)
	{
		if(AController* Ctrl = GetController()){
			if(AGenericController* C = Cast<AGenericController>(Ctrl))
			{
				C->CheckValid = true;
				C->MoveLoc = LocationToMove;

				UE_LOG(LogTemp, Warning, TEXT("MovePTR() Called"));
				ValidHit = false;
			}
		}
	}
}

void AGenericBaseAI::SetPatrolPoints(FVector PointA, FVector PointB)
{

	// Use AIController to move to the next point
	AGenericController* AIController = Cast<AGenericController>(GetController());
	if (AIController)
	{
		AIController->PatrolPointA = PointA;
		AIController->PatrolPointB = PointB;
		AIController->bIsPatrolling = true;

		// Clear Out the patrol elements.
		if (AUserController* PController = Cast<AUserController>(GetController()))
		{
			PController->bPatrolMode=false;
			PController->PatrolPoints.Empty();
		}
	}
}



AAIController* AGenericBaseAI::GetAIController(AGenericBaseAI* Actor)
{
	return Cast<AAIController>(Actor->GetController());
}



// Called when the game starts or when spawned
void AGenericBaseAI::BeginPlay()
{
	Super::BeginPlay();
	
	SelectedDecalComp->SetVisibility(false);
	
	// Cast this to ISelectionInterface
	SelectionInterface = Cast<ISelectionInterface>(this);
}


void AGenericBaseAI::SetupStimulusSource()
{
	StimuliSourcePredator = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	if(StimuliSourcePredator)
	{
		StimuliSourcePredator->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSourcePredator->RegisterWithPerceptionSystem();
	}
}

void AGenericBaseAI::MoveToDes(FVector& Destination)
{
	// Print the hit location coordinates to the output log
	UE_LOG(LogTemp, Warning, TEXT("Hit Location: X=%f, Y=%f, Z=%f"), Destination.X, Destination.Y, Destination.Z);
}

// Called every frame
void AGenericBaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ValidHit)
	{
		MovePTR();
	}

	
	/*if (TargetEnemy)
	{
		if (FVector::Dist(GetActorLocation(), TargetEnemy->GetActorLocation()) <= AttackRange)
		{
			AttackEnemy();
		}
		else
		{
			MoveToEnemy();
		}
	}*/
}

// Called to bind functionality to input
void AGenericBaseAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
