#include "ToolBar/ButtonCommand.h"
#include "ButtonCommand.h"

FButtonCommand::FButtonCommand()
	: TCommands("ContextName", FText::FromString("ContextDesc"), NAME_None, FEditorStyle::GetStyleSetName())
{
}

FButtonCommand::~FButtonCommand()
{
}

void FButtonCommand::RegisterCommands()
{
	UI_COMMAND(CommandInfo, "LoadMesh", "LoadMeshData", EUserInterfaceActionType::Button, FInputChord());
}
