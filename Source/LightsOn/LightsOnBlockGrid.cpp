// Copyright Epic Games, Inc. All Rights Reserved.

#include "LightsOnBlockGrid.h"
#include "LightsOnBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include <list>
#include <vector>
#include <string>

using namespace std;

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ALightsOnBlockGrid::ALightsOnBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	LevelText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	LevelText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	LevelText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	LevelText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Level: {0}"), FText::AsNumber(1)));
	LevelText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;
}


void ALightsOnBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	ResetGrid();
}


void ALightsOnBlockGrid::OnClick(int32 Index) {

	Blocks[Index]->ToggleActive();

	if (Index % Size > 0) {
		Blocks[Index - 1]->ToggleActive();
	}
	if ((Size - Index % Size - 1) > 0) {
		Blocks[Index + 1]->ToggleActive();
	}
	if (((Index - (Index % Size)) / Size) > 0) {
		Blocks[Index - Size]->ToggleActive();
	}
	if ((Size - ((Index - (Index % Size)) / Size) - 1) > 0) {
		Blocks[Index + Size]->ToggleActive();
	}

	if (Blocks[Index]->bIsActive) {
		CheckGrid();
	}
}

bool ALightsOnBlockGrid::CheckGrid()
{
	for (int i = 0; i < Blocks.size(); i++) {
		if (Blocks[i] != nullptr) {
			if (!Blocks[i]->bIsActive) {
				return false;
			}
		}
	}

	return true;
}

void ALightsOnBlockGrid::ResetGrid() 
{
	// Number of blocks
	const int32 NumOfBlocks = Size * Size;

	// Clear and Resize Grid

	if (Blocks.size() > 0){
		for (int i = 0; i < Blocks.size(); i++) {
			Blocks[i]->Destroy();
		}
	}
	Blocks.clear();
	Blocks.resize(NumOfBlocks);
}

void ALightsOnBlockGrid::FillBasicGrid()
{
	// Number of blocks
	const int32 NumOfBlocks = Size * Size;

	// Loop to spawn each block
	for (int32 BlockIndex = 0; BlockIndex < NumOfBlocks; BlockIndex++)
	{
		BlockSpacing = 600.f / (Size - 1);
		const float XOffset = (BlockIndex / Size) * BlockSpacing + (BlockIndex / Size - Size / 2.f) * 900.f * (1 - 2.f / (Size - 1)) / 7.f / (Size / 2.f); // Divide by dimension
		const float YOffset = (BlockIndex % Size) * BlockSpacing + (BlockIndex % Size - Size / 2.f) * 900.f * (1 - 2.f / (Size - 1)) / 7.f / (Size / 2.f); // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		ALightsOnBlock* NewBlock = GetWorld()->SpawnActor<ALightsOnBlock>(BlockLocation, FRotator(0, 0, 0));

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
			NewBlock->AdjustScale(Size);
			NewBlock->Index = BlockIndex;
			Blocks[BlockIndex] = NewBlock;
		}
	}
}

void ALightsOnBlockGrid::AddToGrid(ALightsOnBlock* Block, int32 Index)
{
	Blocks[Index] = Block;
}

void ALightsOnBlockGrid::LoadLevel(int LevelNumber)
{

}

#undef LOCTEXT_NAMESPACE
