// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/ResourceMain.h"
#include "UObject/NoExportTypes.h"
#include "ResourceTransaction.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UResourceTransaction : public UObject
{
	GENERATED_BODY()

	// Mediator Class for Resource Transaction.

public:
	
	int ValueForTransaction = 1;
	
	// Function That initializes the Transaction Process.
	void TransactionProcess(AResourceMain* ResourceRef);

	void ProcessingTransaction(int32 ResourceAmount, EResourceType ResourceType); 
};
