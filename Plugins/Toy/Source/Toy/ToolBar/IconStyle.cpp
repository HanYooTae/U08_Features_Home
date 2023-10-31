#include "ToolBar/IconStyle.h"
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<IconStyle> IconStyle::Instance = nullptr;

TSharedPtr<IconStyle> IconStyle::Get()
{
	// »ý¼º
	if (Instance == nullptr)
		Instance = MakeShareable(new IconStyle());

	return Instance;
}

void IconStyle::ShutDown()
{
	if (Instance.IsValid())
		Instance.Reset();
}

IconStyle::IconStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	FString path = IPluginManager::Get().FindPlugin("Toy")->GetBaseDir();
	path += "/Resources";		// == path /= "Resources";
	StyleSet->SetContentRoot(path);

	FSlateImageBrush* brush = new FSlateImageBrush(path / "Icon.png", FVector2D(48));
	FString name = StyleSetName.ToString() + ".SpawnVertex";
	StyleSet->Set(FName(name), brush);

	//FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode");
}

IconStyle::~IconStyle()
{
}