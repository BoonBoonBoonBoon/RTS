#include "AIContent/GenericBaseEnemy/Ranged/EnemyRangedAI.h"

// Sets default values
AEnemyRangedAI::AEnemyRangedAI()
{
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
 PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyRangedAI::BeginPlay()
{
 Super::BeginPlay();
}

// Called every frame
void AEnemyRangedAI::Tick(float DeltaTime)
{
 Super::Tick(DeltaTime);
}

