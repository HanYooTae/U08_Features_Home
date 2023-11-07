#include "Viewer/MeshViewer.h"

TSharedPtr<FMeshViewer> FMeshViewer::Instance = nullptr;

void FMeshViewer::OpenWindow(UObject* InAsset)
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();
		Instance = nullptr;
	}

	Instance = MakeShareable(new FMeshViewer());

	Instance->OpenWindow_Internal(InAsset);
}

void FMeshViewer::Shutdown()
{
	if (Instance.IsValid())
		Instance.Reset();
}

FName FMeshViewer::GetToolkitFName() const
{
	return FName();
}

FText FMeshViewer::GetBaseToolkitName() const
{
	return FText();
}

FString FMeshViewer::GetWorldCentricTabPrefix() const
{
	return FString();
}

FLinearColor FMeshViewer::GetWorldCentricTabColorScale() const
{
	return FLinearColor();
}

void FMeshViewer::OpenWindow_Internal(UObject* InAsset)
{
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("MeshViewer_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
		);

	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone/*별도의 창으로*/, TSharedPtr<IToolkitHost>(), ToolkitName, layout, true/*검색창*/, true/*툴바아이콘*/, InAsset);
}
