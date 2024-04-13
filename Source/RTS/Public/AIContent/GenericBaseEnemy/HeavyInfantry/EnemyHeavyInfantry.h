#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseEnemy/GenericBaseEnemyAI.h"
#include "EnemyHeavyInfantry.generated.h"

UCLASS()
class RTS_API AEnemyHeavyInfantryAI : public AGenericBaseEnemyAI
{
 GENERATED_BODY()

public:
 // Sets default values for this character's properties
 AEnemyHeavyInfantryAI();

protected:
 // Called when the game starts or when spawned
 virtual void BeginPlay() override;

public:
 // Called every frame
 virtual void Tick(float DeltaTime) override;

 
};