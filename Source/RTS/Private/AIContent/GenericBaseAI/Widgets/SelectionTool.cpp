// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/Widgets/SelectionTool.h"
#include "Engine/Canvas.h"


void ASelectionTool::DrawHUD()
{
	Super::DrawHUD();

	// Get the canvas
	if(Canvas == nullptr)
	{
		return;
	}

	// Set Rectangle properties
	FLinearColor RectColor(0.5f, 0.7f, 1.0f, 0.2f); // Light blue color with alpha 0.2

	// Set the rectangle properties
	FVector2D RectPosition(100.0f, 100.0f);
	FVector2D RectSize(200.0f, 100.0f);
	

	// Draw the rectangle
	Canvas->K2_DrawBox(RectPosition, RectSize, 1.0f, RectColor);
	
}