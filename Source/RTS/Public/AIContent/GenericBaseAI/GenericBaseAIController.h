// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GenericBaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API AGenericBaseAIController : public AAIController
{
	GENERATED_BODY()
public:

	AGenericBaseAIController();

	// Run the behaviour tree immediately. 
	virtual void BeginPlay() override;
	
	// When Pawn is Possessed by controller, initialize the blackboard assets.
	virtual void OnPossess(APawn* InPawn) override;
	
protected:

	/**
	 * Blackboard is the same, but it’s a data store
	 * that the Behavior Tree uses to remember what other actors and locations the actor is behaving using/towards.
	 * It’s your AI’s memory so it knows where to go, who to shoot, etc.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AiSource)
	TObjectPtr<UBlackboardComponent> BBComp;

	/**
	 * Behavior Tree the asset is the data, so the rules you
	 * create that controls how AI characters behave.
	 * It’s like an AI program.
	 */
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BT;
	
	/**
	 * Behavior Tree Component is the actual running component that you attach to an AI character,
	 * which then points to a Behavior Tree asset that controls a character.
	 * It’s your AI’s CPU that actually executes the program (above)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AiSource)
	TObjectPtr<UBehaviorTreeComponent> BTComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;
	
	// Sight
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
};
