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

