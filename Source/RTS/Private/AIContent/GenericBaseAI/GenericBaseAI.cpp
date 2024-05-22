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

	// Initialize the Stimulus Source
    SetupStimulusSource();
	
	// Initialize the Perception System
	//InitializePerceptionSystem();
	
	// Set Tag to building
	Tags.Add("Unit");
		
	// Set the TeamId
	//TeamId = 11;
	
}

void AGenericBaseAI::MyQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
}

/**
 * @brief Moves the AI to a specific location if a valid hit is detected.
 *
 * This function checks if a valid hit is detected. If so, it gets the controller of the AI and casts it to a GenericController.
 * It then sets the CheckValid flag to true and sets the MoveLoc to the location to move to. It also logs a warning message indicating that the function was called.
 * Finally, it sets the ValidHit flag to false.
 */
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

/**
 * @brief Sets the patrol points for the AI.
 *
 * This function gets the controller of the AI and casts it to a GenericController. It then sets the PatrolPointA and PatrolPointB to the given points and sets the bIsPatrolling flag to true.
 * It also checks if the controller can be cast to a UserController. If so, it sets the bPatrolMode flag to false and empties the PatrolPoints array.
 *
 * @param PointA The first patrol point.
 * @param PointB The second patrol point.
 */
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

/**
 * @brief Gets the AI controller of the given actor.
 *
 * This function gets the controller of the given actor and casts it to an AIController.
 *
 * @param Actor The actor to get the AI controller of.
 * @return The AI controller of the given actor.
 */
AAIController* AGenericBaseAI::GetAIController(AGenericBaseAI* Actor)
{
	return Cast<AAIController>(Actor->GetController());
}


void AGenericBaseAI::TakeDamage(float DamageAmount)
{
	// Reduce health by the damage amount
	int Health = this->UnitDataMap[this->UnitType].UnitStats.Health;

	Health -= DamageAmount;
	
	// Log the health
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	// Clamp health between 0 and MaxHealth
	Health = FMath::Clamp(Health, 0.f, 100);
	

	if(Health <= 0)
	{
		Destroy();
	}
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

void AGenericBaseAI::StartAttacking(AActor* Target)
{
	if(AGenericBaseAI* FAi = Cast<AGenericBaseAI>(this))
	{
		if(EnemyTargets.Contains(FAi))
		{
			EnemyTargets[FAi] = Target;
			
			if(EnemyTargets[FAi] == Target)
			{
				CombatInterface->LightInfDealDamage(FAi, Target);
			}
		}
		else
		{
			EnemyTargets.Add(FAi, Target);
		}
	}
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
