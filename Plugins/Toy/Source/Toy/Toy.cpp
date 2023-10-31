#include "Toy.h"
#include "ToolBar/ButtonCommand.h"
#include "LevelEditor.h"

#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
{
	UE_LOG(LogTemp, Error, L"Startup Toy Module");

	// ButtonCommand�� RegisterCommands�Լ��� ȣ���ϴ� �Լ�
	FButtonCommand::Register();

	Extender = MakeShareable(new FExtender());
	
	FToolBarExtensionDelegate toolBarExtensionDelegate = toolBarExtensionDelegate.CreateRaw(this, &FToyModule::AddToolBar);
	Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().SpawnVertexCommand, toolBarExtensionDelegate);

	// Level Editor�� �������� �Լ�
	FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
}

void FToyModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, L"Shutdown Toy Module");
}

void FToyModule::AddToolBar(FToolBarBuilder& InToolBarBuilder)
{
	FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode");
	InToolBarBuilder.AddSeparator();
	InToolBarBuilder.AddToolBarButton
	(
		FButtonCommand::Get().SpawnVertexButton,
		NAME_None,
		FText::FromString("Spawn Vertex"),
		FText::FromString("Spawn Vertex from Binary File"),
		icon
	);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyModule, Toy)