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

void AGenericBaseAI::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		// Set the Target Enemy
		TargetEnemy = Actor;
	}
	else
	{
		// Reset the Target Enemy
		TargetEnemy = nullptr;
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
	
	if (PerceptionComponent && SightConfig)
	{
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AGenericBaseAI::OnTargetPerceptionUpdated);
	}
}

FGenericTeamId AGenericBaseAI::GetGenericTeamId() const
{
	return TeamId;
}


/**
 * @brief Determines the attitude of this AI towards another actor.
 *
 * This function determines the attitude of this AI towards another actor based on their respective teams.
 * It first checks if the other actor is a pawn. If not, it returns a neutral attitude.
 * Then, it checks if the other actor's controller or the other actor itself implements the IGenericTeamAgentInterface.
 * If neither does, it again returns a neutral attitude.
 * It then retrieves the team of the other actor and determines the attitude based on the teams.
 * If they are on the same team, it returns a friendly attitude.
 * If they are on different teams, it returns a hostile attitude.
 * If this AI is not on a team or is on a specific team (in this case, team 2), it returns a neutral attitude.
 *
 * @param Other The other actor to determine the attitude towards.
 * @return The attitude of this AI towards the other actor.
 */
ETeamAttitude::Type AGenericBaseAI::GetTeamAttitudeTowards(const AActor& Other) const
{
	auto OtherPawn = Cast<APawn>(&Other);
	if(OtherPawn == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	// Check if Actor (Bot or Player) implements IGenericTeamAgentInterface.
	auto igtaiActorBot = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
	auto igtaiActorPlayer = Cast<IGenericTeamAgentInterface>(&Other); // Do We need to check the player???
	if(igtaiActorBot == nullptr && igtaiActorPlayer == nullptr) // if Bot is 225
	{
		return ETeamAttitude::Neutral;
	}

	// For Testing, Print ActorBot TeamID.
	
	if(igtaiActorBot != nullptr)
	{
		FGenericTeamId fgtiActorBotTeamId = igtaiActorBot->GetGenericTeamId();
		int iActorBotTeamId = (int)fgtiActorBotTeamId;
		FString fstrActorBotTeamId = FString::FromInt(iActorBotTeamId);
		GEngine->AddOnScreenDebugMessage(-1,15.0f, FColor::Yellow, fstrActorBotTeamId);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *fstrActorBotTeamId);
	}
	// For Testing, Print ActorPlayer TeamID
	if(igtaiActorPlayer != nullptr)
	{
		FGenericTeamId fgtiActorPlayerTeamId = igtaiActorPlayer->GetGenericTeamId();
		int iActorPlayerTeamId = (int)fgtiActorPlayerTeamId;
		FString fstrActorPlayerTeamid = FString::FromInt(iActorPlayerTeamId);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, fstrActorPlayerTeamid);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *fstrActorPlayerTeamid);
	}
	
	
	// Gets the TeamID of the Actor (Bot or Player)
	FGenericTeamId fgtiOtherActorTeamId = NULL;
	if(igtaiActorBot != nullptr)
	{
		fgtiOtherActorTeamId = igtaiActorBot->GetGenericTeamId();
	} else if (igtaiActorPlayer != nullptr)
	{
		fgtiOtherActorTeamId = igtaiActorPlayer->GetGenericTeamId();
	}

	// Determines ThisBot attitude towards the OtherActor (Bot or Player) as either Neutral, Friendly, or Hostile.
	FGenericTeamId fgtiThisBotTeamId = this->GetGenericTeamId();
	if(fgtiThisBotTeamId == 225) // They are not on a team;
	{
		return ETeamAttitude::Neutral;
		
	} else if (fgtiThisBotTeamId == fgtiOtherActorTeamId) // They are on the same team
	{
		return ETeamAttitude::Friendly;
		
	} else if(fgtiThisBotTeamId == 2) // NoiseTrap Team 
	{
		// Noise Trap makes sound ???
		return ETeamAttitude::Neutral;
		
	} else // they are on different teams
	{
		return ETeamAttitude::Hostile;
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
