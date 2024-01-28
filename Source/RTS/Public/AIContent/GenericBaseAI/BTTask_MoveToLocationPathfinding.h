// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToLocationPathfinding.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UBTTask_MoveToLocationPathfinding : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	
	UBTTask_MoveToLocationPathfinding();

	virtual FString GetStaticDescription() const override;

	// For the SelectedUnits Array
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector UnitsArray;
protected:
	
	// Return Type
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

  