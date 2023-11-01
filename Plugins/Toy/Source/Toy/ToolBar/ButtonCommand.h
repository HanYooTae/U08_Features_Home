#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class TOY_API FButtonCommand : public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();

public:
	virtual void RegisterCommands() override;		// 매크로에 등록된 객체를 메모리에 올리기 위한 함수

private:
	void SpawnVertexButton_Pressed();
	void OpenViewerButton_Pressed();

public:
	TSharedPtr<FUICommandInfo> SpawnVertexButton;		// 버튼 객체가 저장
	TSharedPtr<FUICommandInfo> OpenViewerButton;

	TSharedPtr<FUICommandList> SpawnVertexCommand;		// 일종의 Controller
};
