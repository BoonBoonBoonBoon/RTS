// EnemyLightInfantryAI.cpp
#include "AIContent/GenericBaseEnemy/LightInfantry/EnemyLightInfantryAI.h"

// Sets default values
AEnemyLightInfantryAI::AEnemyLightInfantryAI()
{
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
 PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyLightInfantryAI::BeginPlay()
{
 Super::BeginPlay();
}

// Called every frame
void AEnemyLightInfantryAI::Tick(float DeltaTime)
{
 Super::Tick(DeltaTime);
}

