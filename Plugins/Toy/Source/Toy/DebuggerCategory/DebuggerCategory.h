#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

struct FCollectionData
{
	FString Name;
	FVector Location;
	FVector Forward;
};

class TOY_API FDebuggerCategory : public FGameplayDebuggerCategory
{
public:
	FDebuggerCategory();
	~FDebuggerCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();	// DebuggerCategory를 등록할 때는 무조건 이 함수를 통해서 등록해야 함.

public:
	/** [AUTH] gather data for replication */
	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;

	/** [LOCAL] draw collected data */
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

private:
	FCollectionData PlayerPawnData;
	FCollectionData ForwardActorData;
	FCollectionData DebugActorData;
};
