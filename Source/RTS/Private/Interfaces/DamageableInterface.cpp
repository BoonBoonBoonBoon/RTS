// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/DamageableInterface.h"

// Add default functionality here for any IDamageableInterface functions that are not pure virtual.
void IDamageableInterface::TakeDamage(float damage)
{
}

float IDamageableInterface::GetHealth()
{
	return 1;
}

float IDamageableInterface::GetMaxHealth()
{
	return 1;
}
