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

	UFUNCTION(BlueprintCallable)
	virtual void ToggleActive();

	virtual void HandleClicked();

	virtual void Highlight(bool bOn);

	void AdjustScale(int32 Scale);

	void GlassOut();

	void GreyOut();

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
};



