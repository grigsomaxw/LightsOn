// Copyright Epic Games, Inc. All Rights Reserved.

#include "LightsOnBlockGrid.h"
#include "LightsOnBlock.h"
#include "GlassBlock.h"
#include "DeadBlock.h"
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
			if (Blocks[i] != nullptr) {
				Blocks[i]->Destroy();
			}
		}
	}
	Blocks.clear();
	Blocks.resize(NumOfBlocks);
}

void ALightsOnBlockGrid::FillBasicGrid()
{
	ResetGrid();

	// Number of blocks
	const int32 NumOfBlocks = Size * Size;

	for (int i = 0; i < NumOfBlocks; i++) {
		SpawnOnGrid(0, i);
	}
}

void ALightsOnBlockGrid::AddToGrid(ALightsOnBlock* Block, int32 Index)
{
	Block->OwningGrid = this;
	Block->Index = Index;
	Blocks[Index] = Block;
}

void ALightsOnBlockGrid::SpawnOnGrid(int32 BlockType, int32 Index)
{
	BlockSpacing = 600.f / (Size - 1);
	const float XOffset = (Index / Size) * BlockSpacing + (Index / Size - Size / 2.f) * 900.f * (1 - 2.f / (Size - 1)) / 7.f / (Size / 2.f);
	const float YOffset = (Index % Size) * BlockSpacing + (Index % Size - Size / 2.f) * 900.f * (1 - 2.f / (Size - 1)) / 7.f / (Size / 2.f);

	// Make position vector, offset from Grid location
	const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

	ALightsOnBlock* NewBlock;

	switch (BlockType) {
	case 1:
		NewBlock = GetWorld()->SpawnActor<AGlassBlock>(BlockLocation, FRotator(0, 0, 0));
		NewBlock->GlassOut();
		break;
	case 2:
		NewBlock = GetWorld()->SpawnActor<ADeadBlock>(BlockLocation, FRotator(0, 0, 0));
		NewBlock->GreyOut();
		break;
	default:
		NewBlock = GetWorld()->SpawnActor<ALightsOnBlock>(BlockLocation, FRotator(0, 0, 0));
		break;
	}

	if (NewBlock != nullptr)
	{
		NewBlock->OwningGrid = this;
		NewBlock->AdjustScale(Size);
		NewBlock->Index = Index;
		Blocks[Index] = NewBlock;
	}
}

bool ALightsOnBlockGrid::IsBlockActive(int32 Index)
{
	return Blocks[Index]->bIsActive;
}

void ALightsOnBlockGrid::DisableBlock(int32 Index)
{
	if (Blocks[Index]->IsDisabled) {
		Blocks[Index]->IsDisabled = false;
	}
	else {
		Blocks[Index]->IsDisabled = true;
	}
}

void ALightsOnBlockGrid::LoadLevel(int LevelNumber)
{
	switch (LevelNumber) {
		case 0:
			Size = 3;

			ResetGrid();

			SpawnOnGrid(2, 0);
			SpawnOnGrid(1, 1);
			SpawnOnGrid(2, 2);
			SpawnOnGrid(1, 3);
			SpawnOnGrid(0, 4);
			SpawnOnGrid(2, 5);
			SpawnOnGrid(2, 6);
			SpawnOnGrid(1, 7);
			SpawnOnGrid(2, 8);
			break;
		case 1:
			Size = 3;

			ResetGrid();

			SpawnOnGrid(0, 0);
			SpawnOnGrid(2, 1);
			SpawnOnGrid(0, 2);
			SpawnOnGrid(0, 3);
			SpawnOnGrid(0, 4);
			SpawnOnGrid(0, 5);
			SpawnOnGrid(0, 6);
			SpawnOnGrid(1, 7);
			SpawnOnGrid(0, 8);
			break;
		case 2:
			Size = 4;

			ResetGrid();

			SpawnOnGrid(0, 0);
			SpawnOnGrid(0, 1);
			SpawnOnGrid(0, 2);
			SpawnOnGrid(0, 3);
			SpawnOnGrid(0, 4);
			SpawnOnGrid(1, 5);
			SpawnOnGrid(2, 6);
			SpawnOnGrid(0, 7);
			SpawnOnGrid(0, 8);
			SpawnOnGrid(2, 9);
			SpawnOnGrid(1, 10);
			SpawnOnGrid(0, 11);
			SpawnOnGrid(0, 12);
			SpawnOnGrid(0, 13);
			SpawnOnGrid(0, 14);
			SpawnOnGrid(0, 15);
			break;
		case 3:
			Size = 5;

			ResetGrid();

			SpawnOnGrid(1, 0);
			SpawnOnGrid(0, 1);
			SpawnOnGrid(0, 2);
			SpawnOnGrid(0, 3);
			SpawnOnGrid(1, 4);
			SpawnOnGrid(0, 5);
			SpawnOnGrid(2, 6);
			SpawnOnGrid(0, 7);
			SpawnOnGrid(2, 8);
			SpawnOnGrid(0, 9);
			SpawnOnGrid(0, 10);
			SpawnOnGrid(0, 11);
			SpawnOnGrid(0, 12);
			SpawnOnGrid(0, 13);
			SpawnOnGrid(0, 14);
			SpawnOnGrid(0, 15);
			SpawnOnGrid(2, 16);
			SpawnOnGrid(0, 17);
			SpawnOnGrid(2, 18);
			SpawnOnGrid(0, 19);
			SpawnOnGrid(1, 20);
			SpawnOnGrid(0, 21);
			SpawnOnGrid(0, 22);
			SpawnOnGrid(0, 23);
			SpawnOnGrid(1, 24);
			break;
		default:
			Size = 3;

			ResetGrid();

			SpawnOnGrid(0, 0);
			SpawnOnGrid(0, 1);
			SpawnOnGrid(0, 2);
			SpawnOnGrid(0, 3);
			SpawnOnGrid(0, 4);
			SpawnOnGrid(0, 5);
			SpawnOnGrid(0, 6);
			SpawnOnGrid(0, 7);
			SpawnOnGrid(0, 8);
			break;
	}
}

#undef LOCTEXT_NAMESPACE
