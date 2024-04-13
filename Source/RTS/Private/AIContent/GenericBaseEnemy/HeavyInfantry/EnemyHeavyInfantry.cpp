#include "AIContent/GenericBaseEnemy/HeavyInfantry/EnemyHeavyInfantry.h"

// Sets default values
AEnemyHeavyInfantryAI::AEnemyHeavyInfantryAI()
{
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
 PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyHeavyInfantryAI::BeginPlay()
{
 Super::BeginPlay();
}

// Called every frame
void AEnemyHeavyInfantryAI::Tick(float DeltaTime)
{
 Super::Tick(DeltaTime);
}
