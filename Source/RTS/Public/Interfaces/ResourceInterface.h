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
	
	///*virtual FString GetEnumName();
	//virtual void TakeResources(int32 amount);
	//EResourceType GetType(AActor* Actor);
	//virtual int32 GetAmount();
	
	virtual EResourceType GetResourceType() const = 0;

	void AssignResourceType(AActor* Actor);

	AActor* ActorCollect;
};
