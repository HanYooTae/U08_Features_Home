#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class TOY_API FDetailsButton : public IDetailCustomization
{
public:
	TSharedRef<class IDetailCustomization> MakeInstance();

public:
	/** Called when details should be customized */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
};
