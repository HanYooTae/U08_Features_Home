#include "Toy.h"
#include "ToolBar/ButtonCommand.h"
#include "LevelEditor.h"
#include "ToolBar/IconStyle.h"
#include "GameplayDebugger.h"
#include "DebuggerCategory/DebuggerCategory.h"

#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
{
	UE_LOG(LogTemp, Error, L"Startup Toy Module");

	// ToolBar
	{
		FIconStyle::Get();

		// ButtonCommand의 RegisterCommands함수를 호출하는 함수
		FButtonCommand::Register();

		Extender = MakeShareable(new FExtender());

		FToolBarExtensionDelegate toolBarExtensionDelegate = toolBarExtensionDelegate.CreateRaw(this, &FToyModule::AddToolBar_SpawnVertex);
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().SpawnVertexCommand, toolBarExtensionDelegate);

		FToolBarExtensionDelegate toolBarExtensionDelegate2 = toolBarExtensionDelegate2.CreateRaw(this, &FToyModule::AddToolBar_OpenViewer);
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().SpawnVertexCommand, toolBarExtensionDelegate2);

		// Level Editor를 가져오는 함수
		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
	}

	// DebuggerCategory
	{
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get();
		IGameplayDebugger::FOnGetCategory categoryDelegate = IGameplayDebugger::FOnGetCategory::CreateStatic(&FDebuggerCategory::MakeInstance);
		gameplayDebugger.Get().RegisterCategory("AwesomeData", categoryDelegate, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
		gameplayDebugger.NotifyCategoriesChanged();
	}
}

void FToyModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, L"Shutdown Toy Module");

	// IGameplayDebugger가 있다면
	if (IGameplayDebugger::IsAvailable())
		IGameplayDebugger::Get().UnregisterCategory("AwesomData");

	FIconStyle::ShutDown();
}

void FToyModule::AddToolBar_SpawnVertex(FToolBarBuilder& InToolBarBuilder)
{
	//FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode");

	InToolBarBuilder.AddSeparator();
	InToolBarBuilder.AddToolBarButton
	(
		FButtonCommand::Get().SpawnVertexButton,
		NAME_None,
		FText::FromString("Spawn Vertex"),
		FText::FromString("Spawn Vertex from Binary File"),
		FIconStyle::Get()->SpawnVertexButtonIcon
	);
}

void FToyModule::AddToolBar_OpenViewer(FToolBarBuilder& InToolBarBuilder)
{
	InToolBarBuilder.AddToolBarButton
	(
		FButtonCommand::Get().OpenViewerButton,
		NAME_None,
		FText::FromString("Open Viewer"),
		FText::FromString("Open Customization Viewer"),
		FIconStyle::Get()->OpenViewerButtonIcon
	);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyModule, Toy)