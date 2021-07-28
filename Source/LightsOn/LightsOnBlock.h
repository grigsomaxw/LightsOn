// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightsOnBlock.generated.h"

/** A block that can be clicked */
UCLASS(minimalapi)
class ALightsOnBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

public:
	ALightsOnBlock();

	/** Are we currently active? */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	bool bIsActive;

	/** Is the block currently disabled. Used for the tutorial levels. */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	bool IsDisabled;

	/** Grid Index */
	int32 Index;
protected:
	/** Pointer to white material used on the focused block */
	UPROPERTY()
	class UMaterial* BaseMaterial;

	/** Pointer to blue material used on inactive blocks */
	UPROPERTY()
	class UMaterialInstance* BlueMaterial;

	/** Pointer to orange material used on active blocks */
	UPROPERTY()
	class UMaterialInstance* OrangeMaterial;

	/** Pointer to faded glass material used on glass blocks */
	UPROPERTY()
	class UMaterialInstance* GlassMaterial;

	/** Pointer to the faded orange material used on glass blocks */
	UPROPERTY()
	class UMaterialInstance* LitGlassMaterial;

	/** Pointer to grey material used on dead blocks */
	UPROPERTY()
	class UMaterialInstance* GreyMaterial;
public:
	/** Grid that owns us */
	UPROPERTY()
	class ALightsOnBlockGrid* OwningGrid;

	/** Handle the block being clicked */
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	/** Toggle whether the current block is active or not  */
	UFUNCTION(BlueprintCallable)
	virtual void ToggleActive();

	/** Handle the block being clicked  */
	virtual void HandleClicked();

	/** Highlight a block being hovered over */
	virtual void Highlight(bool bOn);

	/** Adjust the scale of the block for larger grids  */
	void AdjustScale(int32 Scale);

	/** Adds the glassy look to the glass block  */
	void GlassOut();

	/** Adds the greyed out look to the dead block  */
	void GreyOut();

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
};



