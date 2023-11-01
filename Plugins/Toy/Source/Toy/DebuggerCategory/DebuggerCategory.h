#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

class TOY_API FDebuggerCategory : public FGameplayDebuggerCategory
{
public:
	FDebuggerCategory();
	~FDebuggerCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();	// DebuggerCategory를 등록할 때는 무조건 이 함수를 통해서 등록해야 함.
};
