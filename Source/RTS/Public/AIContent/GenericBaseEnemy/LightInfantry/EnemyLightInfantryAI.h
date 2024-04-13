#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseEnemy/GenericBaseEnemyAI.h"
#include "EnemyLightInfantryAI.generated.h"

UCLASS()
class RTS_API AEnemyLightInfantryAI : public AGenericBaseEnemyAI
{
 GENERATED_BODY()

public:
 // Sets default values for this character's properties
 AEnemyLightInfantryAI();

protected:
 // Called when the game starts or when spawned
 virtual void BeginPlay() override;

public:
 // Called every frame
 virtual void Tick(float DeltaTime) override;
 
};
