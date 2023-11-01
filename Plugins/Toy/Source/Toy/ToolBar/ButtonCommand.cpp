#include "ButtonCommand.h"
#include "EditorStyleSet.h"

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
	TArray<const FSlateBrush*> brushes;
	FEditorStyle::GetResources(brushes);

	for (const auto& brush : brushes)
		UE_LOG(LogTemp, Warning, L"%s", *brush->GetResourceName().ToString());
}

void FButtonCommand::OpenViewerButton_Pressed()
{
	UE_LOG(LogTemp, Warning, L"Open Viewr Button is Pressed");
}
