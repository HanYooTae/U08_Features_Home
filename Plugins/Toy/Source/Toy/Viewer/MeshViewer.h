#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class TOY_API FMeshViewer : public FAssetEditorToolkit
{
public:
	static void OpenWindow(UObject* InAsset);
	static void Shutdown();

public:
	virtual FName GetToolkitFName() const override;			
	virtual FText GetBaseToolkitName() const override;		
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

private:
	void OpenWindow_Internal(UObject* InAsset);

private:
	static TSharedPtr<FMeshViewer> Instance;
};
