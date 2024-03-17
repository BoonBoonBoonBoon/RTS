// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/ResourceMain.h"
#include "WoodResource.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API AWoodResource : public AResourceMain
{
	GENERATED_BODY()

public:
	AWoodResource();

	virtual void BeginPlay() override;
	
	// Implement the GetType() function declared in the IResourceInterface
	virtual EResourceType GetResourceType() const ;

	// Returns the amount of resource.
	virtual int32 GetAmount();

	// AI takes The Resources.
	int32 TakeResources(int32 amount);

protected:
	int32 MaxResourceAmount;	// The Maximum Amount of Resource a Resource Can Have.
	int32 CurrentResourceAmount;	// The Amount a Resource Currently Has.
	
};