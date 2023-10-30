#include "Toy.h"

#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
{
	UE_LOG(LogTemp, Error, L"Startup Toy Module");

	Extender = MakeShareable(new FExtender());
	
	FToolBarExtensionDelegate toolBarExtensionDelegate = toolBarExtensionDelegate.CreateRaw(this, &FToyModule::AddToolBar);
	Extender->AddToolBarExtension("Compile", EExtensionHook::Before, nullptr, toolBarExtensionDelegate);
}

void FToyModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, L"Shutdown Toy Module");
}

void FToyModule::AddToolBar(FToolBarBuilder& InToolBarBuilder)
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyModule, Toy)