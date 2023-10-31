#pragma once

#include "CoreMinimal.h"

class TOY_API IconStyle
{
public:
	static TSharedPtr<IconStyle> Get();		// Get�� Create�� ������ ������
	static void ShutDown();

public:
	IconStyle();
	~IconStyle();

private:
	static TSharedPtr<IconStyle> Instance;

private:
	const FName StyleSetName = "ToyStyle";
	TSharedPtr<class FSlateStyleSet> StyleSet;
};