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
  */







/**
 * @brief Function that is called every tick and checks if an enemy has been found.
 * If an enemy has been found, it iterates over all friendly AI units that can attack,
 * finds the best location for each unit to attack from, and then moves the unit to that location.
 * @param DeltaTime - The time since the last tick.
 */
void ICombatInterface::CombatTick(float DeltaTime)
{
    /*if(EnemyFound)
    {
        for (AGenericBaseAI* FriendlyActor : AttackingUnits)
        {
            AttackLocation = FindAttackLocation(FriendlyActor);
            MoveToAttackLocation(FriendlyActor, AttackLocation);
        }
    }*/
}


/**
 * @brief Function to find an enemy actor and initiate the attack process.
 * It finds all friendly actors that can attack and initiates the attack process.
 * If there are friendly actors that can attack, it iterates over them and,
 * for each one, it gets its AI controller and moves it to a location.
 * Finally, it sets the current enemy to the provided enemy actor and sets the EnemyFound flag to true.
 * @param EnemyActor - The enemy actor to find.
 * @param FriendlyActors - The array of friendly actors.
 */
void ICombatInterface::FindEnemy(AActor* EnemyActor, TArray<AActor*> FriendlyActors)
{
    // Find all friendly actors that can attack.
    AttackingUnits = ProccessAttackMode(FriendlyActors);

    CurrentEnemy = EnemyActor->GetActorLocation();
    UE_LOG(LogTemp, Warning, TEXT("Actor's location: %s"), *CurrentEnemy.ToString());
    
    for (AGenericBaseAI* FriendlyActor : AttackingUnits)
    {
        AttackLocation = FindAttackLocation(FriendlyActor);
    }
    
    MoveUnitsToSeparateLocations(AttackingUnits, AttackLocation);
   
	
    // Todo : Find locations the AttackingUnits can move to.
	

	
    /*if (AttackingUnits.Num() > 0)
    {
        for(int32 i = 0; i < AttackingUnits.Num(); ++i)
        {
            if (AGenericController* AIController = Cast<AGenericController>(AttackingUnits[i]->GetController()))
            {
                AIController->MoveToLocation(AttackLocation);
            }
        }
    }*/
}

/**
 * @brief Function to process a given array of units and return those that can attack.
 * It iterates over the given array of units. For each unit, it attempts to cast it to an `AGenericBaseAI`.
 * If the cast is successful and the unit's type is in its `UnitDataMap`, it checks if the unit has the `Attack` attribute.
 * If the unit has the `Attack` attribute, it is added to the `UnitsCanAttack` array.
 * The function returns the `UnitsCanAttack` array, which contains all units from the input array that can attack.
 * @param Units - The array of units to process.
 * @return TArray<AGenericBaseAI*> - The array of units that can attack.
 */
TArray<AGenericBaseAI*> ICombatInterface::ProccessAttackMode(TArray<AActor*> Units)
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
}

/**
 * @brief Function to find the best location for a friendly AI unit to attack from.
 * It iterates over all locations within 150 units of the enemy and finds the closest one
 * that is not within 40 units of any other friendly AI unit.
 * @param FriendlyActor - The friendly AI unit.
 * @return FVector - The best location for the friendly AI unit to attack from.
 */
FVector ICombatInterface::FindAttackLocation(AGenericBaseAI* FriendlyActor)
{
    FVector ClosestLocation;
    float MinDis = FLT_MAX;
    FVector enemyLocation = CurrentEnemy;

    // Iterate over all locations within 150 units of the enemy
    for(FVector Location : GetAllLocationsWithinRadius(enemyLocation, MeleeAttackRange))
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

/**
 * @brief Function to get all locations within a certain radius of a given center point.
 * @param center - The center point.
 * @param radius - The radius.
 * @return TArray<FVector> - An array of all locations within the radius of the center point.
 */
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


/**
 * @brief Function to get all locations around an enemy within a certain radius.
 * @param enemyLocation - The location of the enemy.
 * @param radius - The radius around the enemy.
 * @param stepSize - The step size for the grid of points around the enemy.
 * @return TArray<FVector> - An array of all locations around the enemy within the radius.
 */	
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
 */
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

