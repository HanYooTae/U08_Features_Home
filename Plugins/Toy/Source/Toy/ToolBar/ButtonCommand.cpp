#include "ButtonCommand.h"
#include "EditorStyleSet.h"
#include "Interfaces/IMainFrameModule.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Serialization/BufferArchive.h"
#include "DetailPannel/DetailsButton.h"

FButtonCommand::FButtonCommand()
	: TCommands("ContextName", FText::FromString("ContextDesc"), NAME_None, FEditorStyle::GetStyleSetName())
{
	SpawnVertexCommand = MakeShareable(new FUICommandList());
}

FButtonCommand::~FButtonCommand()
{
	if (SpawnVertexCommand.IsValid())
		SpawnVertexCommand.Reset();
}

void FButtonCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(SpawnVertexButton, "SpawnVertexButton", "Spawn Vertex Button", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenViewerButton, "OpenViewerButton", "Open Viewer Button", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE

	FExecuteAction executeAction = FExecuteAction::CreateRaw(this, &FButtonCommand::SpawnVertexButton_Pressed);
	FExecuteAction executeAction2 = FExecuteAction::CreateRaw(this, &FButtonCommand::OpenViewerButton_Pressed);
	SpawnVertexCommand->MapAction(SpawnVertexButton, executeAction);
	SpawnVertexCommand->MapAction(OpenViewerButton, executeAction2);
}

void FButtonCommand::SpawnVertexButton_Pressed()
{
	//UE_LOG(LogTemp, Error, L"SpawnVertexButton_Pressed");
	/*TArray<const FSlateBrush*> brushes;
	FEditorStyle::GetResources(brushes);

	for (const auto& brush : brushes)
		UE_LOG(LogTemp, Warning, L"%s", *brush->GetResourceName().ToString());*/

	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();

	FString path;
	TArray<FString> fileNames;
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();
	platform->OpenFileDialog(handle, "Load", path, "", "Binary File(*.bin)|*.bin", EFileDialogFlags::None, fileNames);
	if (fileNames.Num() < 1) return;

	FBufferArchive buffer;
	FFileHelper::LoadFileToArray(buffer, *fileNames[0]);

	// 읽기
	FMemoryReader reader(buffer, true);
	buffer.Seek(0);		// 처음부터 다시 읽기

	FVertexData data;
	reader << data;
	reader.FlushCache();
	reader.Close();

	GLog->Logf(L"Vertex Count : %d", data.Positions.Num());
	GLog->Logf(L"Index Count : %d", data.Indices.Num());
}

void FButtonCommand::OpenViewerButton_Pressed()
{
	UE_LOG(LogTemp, Warning, L"Open Viewer Button is Pressed");
}
