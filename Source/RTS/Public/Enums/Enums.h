// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

/*
In your provided Enums class,
you've created a utility class to convert enum values to strings. If you have a specific use case where you want to use enums,
let's say for character types or resource types, you can define enums and use them in your classes.
*/


/*
UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Minerals
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

UENUM(BlueprintType)
enum class  ECharacterType : uint8
{
	Worker
};

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString itemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 amount;
};

/**/
/*USTRUCT(BlueprintType)
struct FUnitStats
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float  currentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float  maxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FString unitName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32  team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32  owner;
};
#1#*/

class RTS_API Enums
{
public:
	Enums();
	~Enums();
};