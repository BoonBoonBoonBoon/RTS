// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/ResourceMain.h"
#include "FoodResource.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API AFoodResource : public AResourceMain
{
	GENERATED_BODY()

public:

	AFoodResource();
	
	// Implement the GetType() function declared in the IResourceInterface
	virtual EResourceType GetResourceType() const ;

	// Returns the amount of resource.
	virtual int32 GetAmount() override;

	// AI takes The Resources.
	virtual int32 TakeResources(int32 amount) override;

protected:
	int32 MaxResourceAmount;	// The Maximum Amount of Resource a Resource Can Have.
	int32 CurrentFoodAmount;	// The Amount a Resource Currently Has.
	
	
};
