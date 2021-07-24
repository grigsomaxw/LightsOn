// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightsOnBlock.h"
#include <vector>
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

	/** How many blocks have been clicked */
	int32 Level;

	/** Collection Of Blocks */
	vector<ALightsOnBlock*> Blocks;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

	/** States whether Level has been solved by player*/
	UPROPERTY(Category = Grid, BlueprintReadWrite, EditAnywhere)
	bool LevelSolved;

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

public:

	/** Handle the block being clicked */
	void OnClick(int32 Index);

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetLevelText() const { return LevelText; }

private:
	/** Checks to see if the board has been solved */
	void CheckBoard();

};



