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

	AWoodResource();

	// Implement the GetType() function declared in the IResourceInterface
	virtual EResourceType GetResourceType() const override;
	
};
