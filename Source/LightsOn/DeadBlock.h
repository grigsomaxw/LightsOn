// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LightsOnBlock.h"
#include "DeadBlock.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTSON_API ADeadBlock : public ALightsOnBlock
{
	GENERATED_BODY()

	void HandleClicked();

	void Highlight(bool bOn);

	void ToggleActive();

};
