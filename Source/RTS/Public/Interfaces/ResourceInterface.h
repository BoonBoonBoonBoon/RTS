// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ResourceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UResourceInterface : public UInterface
{
	GENERATED_BODY()
};

UENUM(BlueprintType)
enum class  EResourceType : uint8 {
	Wood,
	Stone,
	Gold,
	Food,
	Invalid,
};

USTRUCT(BlueprintType)
struct FResourceStats
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float  amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	EResourceType resourceType;
};


class RTS_API IResourceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:


	//int ResourceAmount;
	bool bTakingResource;
	
	// Checks The Type of Resource and Returns the Amount.
	void ResourceAmount(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hi);

	// Returns the type of resource.
	virtual EResourceType GetResourceType() const = 0;

	// Returns the amount of resource. (Logs for Debug)
	virtual int32 GetAmount(int Amount);


	// AI Takes the Resources.
	virtual void TakeResources(int32 Amount);
	
};


///*virtual FString GetEnumName();

//EResourceType GetType(AActor* Actor);

