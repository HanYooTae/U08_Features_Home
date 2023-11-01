#include "ToolBar/IconStyle.h"
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FIconStyle> FIconStyle::Instance = nullptr;

TSharedPtr<FIconStyle> FIconStyle::Get()
{
	// ����
	if (Instance == nullptr)
		Instance = MakeShareable(new FIconStyle());

	return Instance;
}

void FIconStyle::ShutDown()
{
	if (Instance.IsValid())
		Instance.Reset();
}

FIconStyle::FIconStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	FString path = IPluginManager::Get().FindPlugin("Toy")->GetBaseDir();
	path += "/Resources";		// == path /= "Resources";
	StyleSet->SetContentRoot(path);

	//FSlateImageBrush* brush = new FSlateImageBrush(path / "Icon.png", FVector2D(48));
	//FString styleName = StyleSetName.ToString() + ".SpawnVertex";
	//StyleSet->Set(FName(styleName), brush);

	//SpawnVertexButtonIcon = FSlateIcon(StyleSetName, FName(styleName));
	
	RegisterIcon("SpawnVertex", path / "Icon.png", FVector2D(48), SpawnVertexButtonIcon);
	RegisterIcon("OpneViewer", path / "Icon2.png", FVector2D(48), OpenViewerButtonIcon);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

FIconStyle::~FIconStyle()
{
	if (StyleSet.IsValid() == false) return;
	
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	// brush�� FSlateStyleSet�� �Ҹ��ڿ��� ���������� ������, delete�� ����ϸ� ��۸� �����Ͱ� ��
	StyleSet.Reset();
}

void FIconStyle::RegisterIcon(const FString& InPostFix, const FString& InPath, const FVector2D& InSize, FSlateIcon& OutSlateIcon)
{
	FSlateImageBrush* brush = new FSlateImageBrush(InPath, InSize);
	FString styleName = StyleSetName.ToString() + "." + InPostFix;
	StyleSet->Set(FName(styleName), brush);

	OutSlateIcon = FSlateIcon(StyleSetName, FName(styleName));
}
