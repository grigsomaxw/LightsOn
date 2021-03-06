// Copyright Epic Games, Inc. All Rights Reserved.

#include "LightsOnBlock.h"
#include "LightsOnBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

ALightsOnBlock::ALightsOnBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> GreyMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> GlassMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> LitGlassMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, GreyMaterial(TEXT("/Game/Puzzle/Meshes/GreyMaterial.GreyMaterial"))
			, GlassMaterial(TEXT("/Game/Puzzle/Meshes/TintedGlass.TintedGlass"))
			, LitGlassMaterial(TEXT("/Game/Puzzle/Meshes/LitGlass.LitGlass"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &ALightsOnBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &ALightsOnBlock::OnFingerPressedBlock);


	// Save a pointer to the materials
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
	GreyMaterial = ConstructorStatics.GreyMaterial.Get();
	GlassMaterial = ConstructorStatics.GlassMaterial.Get();
	LitGlassMaterial = ConstructorStatics.LitGlassMaterial.Get();
}

void ALightsOnBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void ALightsOnBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void ALightsOnBlock::HandleClicked()
{
	if (!IsDisabled)
	{
		OwningGrid->OnClick(Index);
	}
}

void ALightsOnBlock::Highlight(bool bOn)
{
	// Do not highlight if the block has already been activated.
	if (bIsActive || IsDisabled)
	{
		return;
	}

	if (bOn)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, BlueMaterial);
	}
}

void ALightsOnBlock::ToggleActive()
{
	// Change material
	if (!bIsActive)
	{
		BlockMesh->SetMaterial(0, OrangeMaterial);
	}
	else {
		BlockMesh->SetMaterial(0, BlueMaterial);
	}
	bIsActive = !bIsActive;
}

void ALightsOnBlock::AdjustScale(int32 Scale)
{
	BlockMesh->SetRelativeScale3D(FVector((2.f / (Scale - 1)), (2.f / (Scale - 1)), 0.25f));
}

void ALightsOnBlock::GlassOut()
{
	if (!bIsActive)
	{
		BlockMesh->SetMaterial(0, GlassMaterial);
	}
	else {
		BlockMesh->SetMaterial(0, LitGlassMaterial);
	}
}

void ALightsOnBlock::GreyOut()
{
	BlockMesh->SetMaterial(0, GreyMaterial);
}
