// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"
#include "UObject/Interface.h"
#include "UnitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUnitInterface : public UInterface
{
	GENERATED_BODY()
};

UENUM(BlueprintType)
enum class EUnitTypes : uint8
{
	Worker, 
	LightInfantry,
	Scout,
	Siege,
	Ranged,
	HeavyInfantry,
	Harasser,
	Transport,
	Invalid,
};


USTRUCT()
struct FUnitStats
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category= "Health")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageDealt;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed;
	
	UPROPERTY(EditAnywhere, Category = "UnitType")
	EUnitTypes UnitType;
};



UENUM()
enum class EUnitAttributes
{
	Gather,
	Attack,
	Repair,
	Build,
	Guard,
	Patrol,
	Shoot,
	Transport,
	Search,
	Invalid,
};



/**
 * 
 */
class RTS_API IUnitInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Check if a specific element is in the array.
	static bool IsUnitSelected(const TArray<AActor*>& UnitArray, const AActor* UnitToCheck);

	EUnitTypes GetUnitType(const AActor* UnitActor);

	EUnitTypes AssignUnitType(const AActor* UnitActor);;
};
