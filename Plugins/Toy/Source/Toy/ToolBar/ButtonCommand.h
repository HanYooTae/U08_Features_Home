#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class TOY_API FButtonCommand : public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();

protected:
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> CommandInfo;		// 버튼 객체가 저장
};
