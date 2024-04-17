// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "UserController.h"
#include "AIContent/GenericBaseAI/GenericController.h"
#include "Components/DecalComponent.h"
#include "Perception/AIPerceptionComponent.h"
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

	// Initialize the Stimulus Source
    SetupStimulusSource();
	
	// Initialize the Perception System
	InitializePerceptionSystem();
	
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

	// Initialize the CombatInterface
	CombatInterface = Cast<ICombatInterface>(this);


}


void AGenericBaseAI::SetupStimulusSource()
{
	StimuliSourceAi = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	if(StimuliSourceAi)
	{
		StimuliSourceAi->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSourceAi->RegisterWithPerceptionSystem();
	}
}

void AGenericBaseAI::InitializePerceptionSystem()
{
	// Initialize the Perception Component
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	
	// Initialize the Sight Config
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (SightConfig)
	{
		SightConfig->SightRadius = 1000.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 100000.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

		PerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
		PerceptionComponent->ConfigureSense(*SightConfig);
	}
	
	/*if (PerceptionComponent && SightConfig)
	{
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AGenericBaseAI::OnTargetPerceptionUpdated);
	}*/
}


// Called every frame
void AGenericBaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ValidHit)
	{
		MovePTR();
	}
}

// Called to bind functionality to input
void AGenericBaseAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
