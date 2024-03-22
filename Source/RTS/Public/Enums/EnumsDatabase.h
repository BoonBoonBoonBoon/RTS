// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumsDatabase.generated.h"


/*UENUM(BlueprintType)
enum class  EResourceType : uint8 {
	Wood,
	Stone,
	Gold,
	Food
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
};*/

/*
UENUM(BlueprintType)
enum class  ECharacterType : uint8 {
	Worker,
	Military,
	Animal,
	End
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

USTRUCT(BlueprintType)
struct FInventory
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TArray<FItem> items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int32 capacity;

	FItem* FindItem(FString itemName) {
		for (FItem& item : items) {
			if (item.itemName.Equals(itemName)) {
				return &item;
			}
		}
		return NULL;
	}
};

USTRUCT(BlueprintType)
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
*/


/*
USTRUCT(BlueprintType)
struct FBuildingStats :  public FUnitStats
{
	GENERATED_USTRUCT_BODY()
public:
		
	
};
*/



/*
USTRUCT(BlueprintType)
struct FCharacterStats : public FUnitStats
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32  carryWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		ECharacterType characterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32  gatherAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FInventory inventory;
};
*/

UCLASS()
class RTS_API UEnumsDatabase : public UObject
{
	GENERATED_BODY()
	
public:
	
		//EBuildingTypes GetBuildingType(AMainBuilding)
	
};
