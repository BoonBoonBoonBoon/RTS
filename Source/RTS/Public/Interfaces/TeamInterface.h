// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TeamInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTeamInterface : public UInterface
{
	GENERATED_BODY()
};

/**
* In Unreal Engine, making use of an interface involves defining a set of functions in an interface class and then implementing those functions in other classes.
* Interfaces are a way to achieve a form of multiple inheritance,
* allowing different classes to share common functionality without having a direct hierarchical relationship. 
 */
class RTS_API ITeamInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual int32 GetTeam();
	virtual int32 GetOwningPlayer();
	
};
