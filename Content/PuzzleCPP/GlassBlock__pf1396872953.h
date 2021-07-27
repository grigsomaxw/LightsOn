#pragma once
#include "Blueprint/BlueprintSupport.h"
#include "LightsOn/GlassBlock.h"
class UStaticMeshComponent;
#include "GlassBlock__pf1396872953.generated.h"
UCLASS(config=Engine, Blueprintable, BlueprintType, meta=(ReplaceConverted="/Game/MyStuff/GlassBlock.GlassBlock_C", OverrideNativeName="GlassBlock_C"))
class AGlassBlock_C__pf1396872953 : public AGlassBlock
{
public:
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="Plane"))
	UStaticMeshComponent* bpv__Plane__pf;
	AGlassBlock_C__pf1396872953(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	static void __CustomDynamicClassInitialization(UDynamicClass* InDynamicClass);
	static void __StaticDependenciesAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	static void __StaticDependencies_DirectlyUsedAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
public:
};
