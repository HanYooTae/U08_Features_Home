#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class TOY_API FButtonCommand : public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();

public:
	virtual void RegisterCommands() override;		// ��ũ�ο� ��ϵ� ��ü�� �޸𸮿� �ø��� ���� �Լ�

private:
	void SpawnVertexButton_Pressed();

public:
	TSharedPtr<FUICommandInfo> SpawnVertexButton;		// ��ư ��ü�� ����
	TSharedPtr<FUICommandList> SpawnVertexCommand;
};
