// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightsOnBlock.h"
#include <vector>
#include <string>
#include "LightsOnBlockGrid.generated.h"

using namespace std;

/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class ALightsOnBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** Text component for the level */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* LevelText;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* CongratulationsText;

public:
	ALightsOnBlockGrid();

	/** Collection Of Blocks */
	vector<ALightsOnBlock*> Blocks;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadWrite)
	int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadWrite)
	float BlockSpacing;

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

public:

	/** Handle the block being clicked */
	UFUNCTION(BlueprintCallable)
	void OnClick(int32 Index);

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetLevelText() const { return LevelText; }

	/** Checks to see if the board has been solved */
	UFUNCTION(BlueprintCallable)
	bool CheckGrid();

	/** Resets the grid, destroying and removing any blocks currently stored */
	UFUNCTION(BlueprintCallable)
	void ResetGrid();

	/** Fills the grid with basic blocks */
	UFUNCTION(BlueprintCallable)
	void FillBasicGrid();

	/** Adds a given block to the grid at a given index */
	UFUNCTION(BlueprintCallable)
	void AddToGrid(ALightsOnBlock* Block, int32 Index);

	/** Spawns a block of the requested type (0 - Basic, 1 - Glass, 2 - Dead) at the given index. */
	UFUNCTION(BlueprintCallable)
	void SpawnOnGrid(int32 BlockType, int32 Index);

	/** Loads a preset level associated with the given number */
	UFUNCTION(BlueprintCallable)
	void LoadLevel(int LevelNumber);

	/** Checks whether the block at a given index is active */
	UFUNCTION(BlueprintCallable)
	bool IsBlockActive(int32 Index);

	/** Disables a block at the given index. Used only for the tutorial */
	UFUNCTION(BlueprintCallable)
	void DisableBlock(int32 Index);

};



