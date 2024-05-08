// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/CombatInterface.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "AIContent/GenericBaseAI/GenericController.h"
#include "AIContent/GenericBaseEnemy/GenericBaseEnemyAI.h"

/*	Todo : W/O Perception Currently. 
  *	The Friendly AI that can attack must find an actor that they can attack. 
  *	They do this when the player clicks on the Enemy AI target in usercontroller event key.
  *	Once we find the ai target the friendly AI must be constantly updated about where the enemy ai is currently at in the combatinterface,
  *	we can do this by checking if we have found an enemy and in the combattick function check if the boolean is true.
  *	if its true the enemy will constantly move to the currently found enemy ai.
  *	to do this we then must make a function where the friendly ai that have the Attack attribute will find the closest location to the enemy ai.
  *	this location must not be no further than 150 units away from the enemy ai.
  *	furthermore, the friendly ai must ignore the exact and nearby locations of the friendly ai that are also attacking the enemy ai, this should be no more than 40 units.
  *	Once these conditions are met the friendly ai will move to the location and attack the enemy ai.
  *	if we also then have new incoming friendlies after the initial attack, they will also move to the enemy ai and attack and find themselves a location to attack from.
  * 
  * 
  */


void ICombatInterface::FindEnemy(AActor* EnemyActor, TArray<AActor*> FriendlyActors)
{
    // Fires off when we select an enemy to go to.
    // stores all selected units.
    // Need to find the selected units that can attack, and assign them their own array
    // and find the enemy and assign it its own variable.

    if (IsValid(EnemyActor))
    {
        // Find all friendly actors that can attack.
        AttackingUnits = ProccessAttackMode(FriendlyActors);

        //AttackCommenced = true;

        // Find Enemy Location.
        CurrentEnemy = EnemyActor->GetActorLocation();

        UE_LOG(LogTemp, Warning, TEXT("Attacking Actors After process %d"), AttackingUnits.Num());

        UE_LOG(LogTemp, Warning, TEXT("Actor's location: %s"), *CurrentEnemy.ToString());

        for (AGenericBaseAI* FriendlyActor : AttackingUnits)
        {
           FriendlyActor->EnemyTargets.Add(FriendlyActor, EnemyActor);

            AttackLocation = FindAttackLocation(FriendlyActor);
        }
        MoveUnitsToSeparateLocations(AttackingUnits, AttackLocation);
    }
}


TArray<AGenericBaseAI*> ICombatInterface::ProccessAttackMode(TArray<AActor*> Units)
{
    TArray<AGenericBaseAI*> UnitsCanAttack;

    for (AActor* Src : Units)
    {
        if (auto GenActor = Cast<AGenericBaseAI>(Src))
        {
            if (GenActor->UnitDataMap.Contains(GenActor->UnitType))
            {
                if (TArray<EUnitAttributes> Att = GenActor->UnitDataMap[GenActor->UnitType].Attributes; Att.Contains(
                    EUnitAttributes::Attack))
                {
                    UnitsCanAttack.AddUnique(GenActor);
                }
            }
        }
    }
    // Log the amount of units that will be returned
    UE_LOG(LogTemp, Warning, TEXT("Amount of units that will be returned: %d"), UnitsCanAttack.Num());

    return UnitsCanAttack;
}

FVector ICombatInterface::FindAttackLocation(AGenericBaseAI* FriendlyActor)
{
    FVector ClosestLocation;
    float MinDis = FLT_MAX;
    FVector enemyLocation = CurrentEnemy;

    // Iterate over all locations within 150 units of the enemy
    for (FVector Location : GetAllLocationsWithinRadius(enemyLocation, MeleeAttackRange))
    {
        // Check if the location is within 40 units of any other friendly actor.
        if (!IsLocationOccupied(Location, AttackingUnits, 40.0f))
        {
            float Distance = FVector::Dist(Location, FriendlyActor->GetActorLocation());
            if (Distance < MinDis)
            {
                MinDis = Distance;
                ClosestLocation = Location;
            }
        }
    }
    return ClosestLocation;
}


TArray<FVector> ICombatInterface::GetAllLocationsWithinRadius(FVector center, float radius)
{
    TArray<FVector> locationsWithinRadius;
    TArray<FVector> allLocations = GetAllLocationsAroundEnemy(center, radius, 10.f);

    for (FVector location : allLocations)
    {
        if (FVector::Dist(center, location) <= radius)
        {
            locationsWithinRadius.Add(location);
        }
    }

    return locationsWithinRadius;
}


void ICombatInterface::StartAttacking(AActor* Target)
{
}

void ICombatInterface::LightInfDealDamage(AGenericBaseAI* Unit, AActor* Target)
{
    if(IsValid(Target))
    {
        // Get Damage to deal from the unit's stats.
        int DmgToDeal = Unit->UnitDataMap[Unit->UnitType].UnitStats.DamageDealt;

        // Get the attack speed from the unit's stats.
        int AttackSpeed = Unit->UnitDataMap[Unit->UnitType].UnitStats.AttackSpeed;

        if (TimeValue <= 0)
        {
            TimeValue = AttackSpeed;
        }
    
        // Check if the timer is already set
        if (!Unit->GetWorld()->GetTimerManager().IsTimerActive(Unit->AttackTimerHandleLightInf))
        {
            // lambda function, Set a timer to call the AttackEnemy function every 2 seconds
            Unit->GetWorld()->GetTimerManager().SetTimer(Unit->AttackTimerHandleLightInf, [this, Unit, Target, DmgToDeal]()
            {
                TimeValue--;

                UE_LOG(LogTemp, Warning, TEXT("Remaining time for timer: %d"), TimeValue);

                if (TimeValue <= 0)
                {
                    //TimeValue = Unit->UnitDataMap[Unit->UnitType].UnitStats.AttackSpeed;
                    if (AGenericBaseEnemyAI* Enemy = Cast<AGenericBaseEnemyAI>(Target))
                    {
                        Enemy->TakeDamage(DmgToDeal);
                        
                        if (Enemy->Health <= 0)
                        {
                            Unit->GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandleLightInf);
                        }
                    }
                }
            }, AttackSpeed, true);
        }
    }
    
    /*
    FTimerHandle& ActorTimer = LightInfTimers[Unit]; // Get the timer for the actor.
    Unit->GetWorld()->GetTimerManager().SetTimer(ActorTimer, [&, Unit, Target, DmgToDeal]()
    {
        
        // Deal damage to the enemy
        if (AGenericBaseEnemyAI* Enemy = Cast<AGenericBaseEnemyAI>(Target))
        {
            --TimeValue;
            if(TimeValue <= 0)
            {
                TimeValue = Unit->UnitDataMap[Unit->UnitType].UnitStats.AttackSpeed;
                Enemy->TakeDamage(DmgToDeal);
            }
        }
    }, AttackSpeed, true);
    */
    
  
    
    /*if(AGenericBaseEnemyAI* Enemy = Cast<AGenericBaseEnemyAI>(Target))
    {
        Enemy->TakeDamage(DmgToDeal);
    }*/
}


TArray<FVector> ICombatInterface::GetAllLocationsAroundEnemy(FVector enemyLocation, float radius, float stepSize)
{
    TArray<FVector> locations;

    // Iterate over a grid of points around the enemy's location
    for (float phi = 0.0f; phi <= PI; phi += stepSize) // phi is the angle from the positive z-axis
    {
        for (float theta = 0.0f; theta <= 2 * PI; theta += stepSize) // theta is the angle from the positive x-axis
        {
            float x = radius * sin(phi) * cos(theta);
            float y = radius * sin(phi) * sin(theta);
            float z = radius * cos(phi);

            // Add each point to the array of locations
            locations.Add(enemyLocation + FVector(x, y, z));
        }
    }

    return locations;
}

void ICombatInterface::MoveUnitsToSeparateLocations(TArray<AGenericBaseAI*> FriendlyActors, FVector TargetLocation)
{
    int32 NumUnits = FriendlyActors.Num();
    float Radius = 100.0f * NumUnits; // Adjust this value as needed
    float AngleBetweenUnits = 2 * PI / NumUnits;

    for (int32 i = 0; i < NumUnits; ++i)
    {
        float Angle = AngleBetweenUnits * i;
        FVector UnitTargetLocation = TargetLocation + Radius * FVector(cos(Angle), sin(Angle), 0);

        if (AGenericController* AIController = Cast<AGenericController>(FriendlyActors[i]->GetController()))
        {
            AIController->MoveToLocation(UnitTargetLocation);
        }
    }
}


bool ICombatInterface::IsLocationOccupied(FVector Location, TArray<AGenericBaseAI*> FriendlyActors, float Radius)
{
    for (AGenericBaseAI* Actor : FriendlyActors)
    {
        if (FVector::Dist(Location, Actor->GetActorLocation()) < Radius)
        {
            return true;
        }
    }
    return false;
}



/**
 * @brief Function to move a friendly AI unit to a given attack location.
 * @param FriendlyActor - The friendly AI unit.
 * @param AttackLocation - The location to move to.
 */
/*
void ICombatInterface::MoveToAttackLocation(AGenericBaseAI* FriendlyActor, FVector AttackLocation)
{
    if(AGenericController* AIController = Cast<AGenericController>(FriendlyActor->GetController()))
    {
        AIController->MoveToLocation(AttackLocation);
    }
}
*/







//------------------------------------------------------------





/*
// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/CombatInterface.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "AIContent/GenericBaseAI/GenericController.h"

 /*	Todo : W/O Perception Currently. 
  *	The Friendly AI that can attack must find an actor that they can attack. 
  *	They do this when the player clicks on the Enemy AI target in usercontroller event key.
  *	Once we find the ai target the friendly AI must be constantly updated about where the enemy ai is currently at in the combatinterface,
  *	we can do this by checking if we have found an enemy and in the combattick function check if the boolean is true.
  *	if its true the enemy will constantly move to the currently found enemy ai.
  *	to do this we then must make a function where the friendly ai that have the Attack attribute will find the closest location to the enemy ai.
  *	this location must not be no further than 150 units away from the enemy ai.
  *	furthermore, the friendly ai must ignore the exact and nearby locations of the friendly ai that are also attacking the enemy ai, this should be no more than 40 units.
  *	Once these conditions are met the friendly ai will move to the location and attack the enemy ai.
  *	if we also then have new incoming friendlies after the initial attack, they will also move to the enemy ai and attack and find themselves a location to attack from.
  * 
  * 
  #1#
/*CurrentEnemy = EnemyActor->GetActorLocation();
  UE_LOG(LogTemp, Warning, TEXT("Actor's location: %s"), *CurrentEnemy.ToString());
  
  for (AGenericBaseAI* FriendlyActor : AttackingUnits)
  {
      AttackLocation = FindAttackLocation(FriendlyActor);
  }
  MoveUnitsToSeparateLocations(AttackingUnits, AttackLocation);#1#
// Find all friendly actors that can attack.
//AttackingUnits = ProccessAttackMode(FriendlyActors);
//  UE_LOG(LogTemp, Warning, TEXT("Attacking Units: %d"), AttackingUnits.Num());
//UE_LOG(LogTemp, Warning, TEXT("bUnitFound: %s"), bUnitFound ? TEXT("True") : TEXT("False"));


/**
 * @brief Checks if a given FVector value exists in a TMap that maps AGenericBaseAI pointers to FVectors.
 * @param Map The TMap to search in. It maps AGenericBaseAI pointers to FVectors.
 * @param Value The FVector value to search for.
 * @return true if the FVector value is found in the TMap, false otherwise.
 #1#
bool ContainsValue(TMap<AGenericBaseAI*, FVector>& Map, FVector Value)
{
    for (auto& Elem : Map)
    {
        if (Elem.Value == Value)
        {
            return true;
        }
    }
    return false;
}


// V--- This should maybe be looking for if we found an enemy.


void ICombatInterface::FindEnemy(AActor* EnemyActor, TArray<AActor*> FriendlyActors)
{
    CurrentEnemy = EnemyActor->GetActorLocation(); // Obtain the location of the enemy actor.
  //  UE_LOG(LogTemp, Warning, TEXT("enemy location: %s"), *CurrentEnemy.ToString());
   // UE_LOG(LogTemp, Warning, TEXT("Friendly %d actors"), FriendlyActors.Num());
   bUnitFound = AttackingUnits.Num() > 0; // For us to attack.
    
    // Proccess the actors that can attack.
    ProccessActors(FriendlyActors);

    /#1#/ If we have found an enemy, we will find the closest location to the enemy.
    for (AGenericBaseAI* Src : AttackingUnits)
    {
        FVector Location = FindAttackLocation(Src);
        Src->ActorLocationMap.Add(Src, Location); // Update the ActorLocationMap
        
        /*for (auto& Elem : Src->ActorLocationMap)
        {
            AGenericBaseAI* ActorV = Elem.Key;
            FVector LocationV = Elem.Value;

            UE_LOG(LogTemp, Warning, TEXT("Actor: %s, Location: %s"), *ActorV->GetName(), *LocationV.ToString());
        }#2#
    }#1#
}

void ICombatInterface::ProccessActors(TArray<AActor*> Array)
{
    UE_LOG(LogTemp, Warning, TEXT("AttackingUnits %d actors BEFORE"), AttackingUnits.Num());
    
    for (AActor* Actor : Array)
    {
        if (AGenericBaseAI* Unit = Cast<AGenericBaseAI>(Actor))
        {
           // AttackingUnits.Add(Unit);
            AttackingUnits = ProccessAttackMode(Unit);
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("AttackingUnits %d actors"), AttackingUnits.Num());
}

/#1#/ UE_LOG(LogTemp, Warning, TEXT("Processing %d actors"), Array.Num());
for (AActor* Src : Array)
{
    if (auto Unit = Cast<AGenericBaseAI>(Src))
    {
        AttackingUnits.Add(Unit);
        AttackingUnits = ProccessAttackMode(Unit);

        // Calculate the distance between the AI and the target
        // float distance = FVector::Dist(Unit->GetActorLocation(), CurrentEnemy);
    }
}
UE_LOG(LogTemp, Warning, TEXT("Attacking Units: %d"), AttackingUnits.Num());#1#

TArray<AGenericBaseAI*> ICombatInterface::ProccessAttackMode(AActor* Units)
{
    TArray<AGenericBaseAI*> UnitsCanAttack;

    if (auto GenActor = Cast<AGenericBaseAI>(Units))
    {
        if (GenActor->UnitDataMap.Contains(GenActor->UnitType))
        {
            if (TArray<EUnitAttributes> Att = GenActor->UnitDataMap[GenActor->UnitType].Attributes; Att.Contains(
                EUnitAttributes::Attack))
            {
                UnitsCanAttack.AddUnique(GenActor);
            }
        }
   }

    // Log the amount of units that will be returned
    UE_LOG(LogTemp, Warning, TEXT("Processing %d actors"), UnitsCanAttack.Num());
    return UnitsCanAttack;
}

FVector ICombatInterface::FindAttackLocation(AGenericBaseAI* FriendlyActor)
{
    FVector ClosestLocation;
    float MinDis = FLT_MAX;
    FVector enemyLocation = CurrentEnemy;
    TArray<FVector> lo;
    
    // Iterate over all locations within 150 units of the enemy
    for(FVector Location : GetAllLocationsWithinRadius(enemyLocation, MeleeAttackRange))
    {
        lo.Add(Location);
        UE_LOG(LogTemp, Warning, TEXT("lo: %d"), lo.Num());
        /#1#/ Check if the location is within 40 units of any other friendly actor.
       if (!IsLocationOccupied(Location, AttackingUnits, 40.0f) && !ContainsValue(FriendlyActor->ActorLocationMap, Location)) // Check if the location is already assigned to any actor // Problem is this checks, when we have not yet moved to the location. 
        {
            float Distance = FVector::Dist(Location, FriendlyActor->GetActorLocation());
            if (Distance < MinDis)
            {
                MinDis = Distance;
                ClosestLocation = Location;
            }
        }#1#
    }
    // Add the location to the ActorLocationMap
    FriendlyActor->ActorLocationMap.Add(FriendlyActor, ClosestLocation);
    return ClosestLocation;
}

/**
 * @brief Function to get all locations within a certain radius of a given center point.
 * @param center - The center point.
 * @param radius - The radius.
 * @return TArray<FVector> - An array of all locations within the radius of the center point.
 #1#
TArray<FVector> ICombatInterface::GetAllLocationsWithinRadius(FVector center, float radius)
{
    TArray<FVector> locationsWithinRadius;
    TArray<FVector> allLocations = GetAllLocationsAroundEnemy(center, radius, 40.f);

    for (FVector location : allLocations)
    {
        if (FVector::Dist(center, location) <= radius)
        {
            locationsWithinRadius.Add(location);
        }
    }
    return locationsWithinRadius;
}









/*TArray<AGenericBaseAI*> ICombatInterface::ProccessAttackMode(TArray<AActor*> Units)
{
    TArray<AGenericBaseAI*> UnitsCanAttack;

    for (AActor* Src : Units)
    {
        if (auto GenActor = Cast<AGenericBaseAI>(Src))
        {
            if(GenActor->UnitDataMap.Contains(GenActor->UnitType))
            {
                if(TArray<EUnitAttributes> Att = GenActor->UnitDataMap[GenActor->UnitType].Attributes; Att.Contains(EUnitAttributes::Attack))
                {
                    UnitsCanAttack.AddUnique(GenActor);
                }
            }
        }
    }
    // Log the amount of units that will be returned
    UE_LOG(LogTemp, Warning, TEXT("Amount of units that will be returned: %d"), UnitsCanAttack.Num());
    return UnitsCanAttack;
}#1#


void ICombatInterface::AttackEnemy()
{
    UE_LOG(LogTemp, Warning, TEXT("AttackEnemy"));
}

/#1#/ Get the world from the unit
       UWorld* World = Unit->GetWorld();
       if (World)
       {
           // Set a timer to call the AttackEnemy function every second
           World->GetTimerManager().SetTimer(Unit->AttackTimerHandle, Unit, &AGenericBaseAI::AttackEnemy, 1.0f, true);
       }
   }
   else
   {
       // If not attacking, clear the timer
       if (Unit->AttackTimerHandle.IsValid())
       {
           Unit->GetWorld()->GetTimerManager().ClearTimer(Unit->AttackTimerHandle);
       }#1#

/*
// UE_LOG(LogTemp, Warning, TEXT("InitiateCombat"));
// Get the damage modifier for the friendly unit and cast that damage to the enemies health.
// Also get a timer or something to modify the time it takes to attack the enemy
        
// Get the world from the current context
UWorld* World = Unit->GetWorld();
if (!World) return;

// Get the timer manager
FTimerManager& TimerManager = World->GetTimerManager();

// Access the UnitStats from the unitData
FUnitData unitData = Unit->UnitDataMap[Unit->UnitType];

// Set up a timer to call the AttackEnemy function every AttackSpeed seconds
TimerManager.SetTimer(AttackTimerHandle, Unit, &ICombatInterface::AttackEnemy, unitData.UnitStats.AttackSpeed, true);
#1#

/**
 * @brief Function to find the best location for a friendly AI unit to attack from.
 * It iterates over all locations within 150 units of the enemy and finds the closest one
 * that is not within 40 units of any other friendly AI unit.
 * @param FriendlyActor - The friendly AI unit.
 * @return FVector - The best location for the friendly AI unit to attack from.
 #1#




/**
 * @brief Function to get all locations around an enemy within a certain radius.
 * @param enemyLocation - The location of the enemy.
 * @param radius - The radius around the enemy.
 * @param stepSize - The step size for the grid of points around the enemy.
 * @return TArray<FVector> - An array of all locations around the enemy within the radius.
 #1#	
TArray<FVector> ICombatInterface::GetAllLocationsAroundEnemy(FVector enemyLocation, float radius, float stepSize)
{
    TArray<FVector> locations;

    // Iterate over a grid of points around the enemy's location
    for (float phi = 0.0f; phi <= PI; phi += stepSize) // phi is the angle from the positive z-axis
    {
        for (float theta = 0.0f; theta <= 2*PI; theta += stepSize) // theta is the angle from the positive x-axis
        {
            float x = radius * sin(phi) * cos(theta);
            float y = radius * sin(phi) * sin(theta);
            float z = radius * cos(phi);

            // Add each point to the array of locations
            locations.Add(enemyLocation + FVector(x, y, z));
        }
    }

    return locations;
}

/**
 * @brief Function to move friendly AI units to separate locations.
 * It calculates a circular formation around the target location and moves each unit to a unique position on the circle's circumference.
 * @param FriendlyActors - The array of friendly AI units.
 * @param TargetLocation - The target location.
 #1#
void ICombatInterface::MoveUnitsToSeparateLocations(TArray<AGenericBaseAI*> FriendlyActors, FVector TargetLocation)
{
    int32 NumUnits = FriendlyActors.Num();
    float Radius = 100.0f * NumUnits; // Adjust this value as needed
    float AngleBetweenUnits = 2 * PI / NumUnits;

    for (int32 i = 0; i < NumUnits; ++i)
    {
        float Angle = AngleBetweenUnits * i;
        FVector UnitTargetLocation = TargetLocation + Radius * FVector(cos(Angle), sin(Angle), 0);

        if (AGenericController* AIController = Cast<AGenericController>(FriendlyActors[i]->GetController()))
        {
            AIController->MoveToLocation(UnitTargetLocation);
        }
    }
}

/**
 * @brief Function to check if a given location is within a certain radius of any friendly AI unit.
 * @param Location - The location to check.
 * @param FriendlyActors - The array of friendly AI units.
 * @param Radius - The radius.
 * @return bool - True if the location is within the radius of any friendly AI unit, false otherwise.
 #1#
bool ICombatInterface::IsLocationOccupied(FVector Location, TArray<AGenericBaseAI*> FriendlyActors, float Radius)
{
    for (AGenericBaseAI* Actor : FriendlyActors)
    {
        if (FVector::Dist(Location, Actor->GetActorLocation()) < Radius)
        {
            return true;
        }
    }
    return false;
}
*/


