// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadBlock.h"
#include "LightsOnBlock.h"
#include "LightsOnBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

void ADeadBlock::HandleClicked()
{
	return;
}

void ADeadBlock::Highlight(bool bOn)
{
	return;
}

void ADeadBlock::ToggleActive()
{
	bIsActive = true;
}