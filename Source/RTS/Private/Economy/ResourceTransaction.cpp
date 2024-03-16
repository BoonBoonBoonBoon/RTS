// Fill out your copyright notice in the Description page of Project Settings.


#include "Economy/ResourceTransaction.h"
#include "Resources/WoodResource.h"


void UResourceTransaction::TransactionProcess(AResourceMain* ResourceRef)
{
	if(Cast<AWoodResource>(ResourceRef))
	{
		if(AWoodResource* WoodResource = Cast<AWoodResource>(ResourceRef))
		{
			UE_LOG(LogTemp, Warning, TEXT("Transaction Process Fired Up(WOOD)"));
			WoodResource->TakeResources(ValueForTransaction);
		}
	}
	else if(Cast<AResourceMain>(ResourceRef))
	{
		UE_LOG(LogTemp, Warning, TEXT("Transaction Process Fired Up (MAIN)"));
	}
}
