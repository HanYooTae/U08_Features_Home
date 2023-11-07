#include "ButtonCommand.h"
#include "EditorStyleSet.h"
#include "Interfaces/IMainFrameModule.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Serialization/BufferArchive.h"
#include "DetailPannel/DetailsButton.h"
#include "LevelEditorViewport.h"
#include "RHI/CLoadMesh.h"
#include "Misc/FileHelper.h"
#include "Viewer/MeshViewer.h"
#include "Assets/CDetailAsset.h"

FButtonCommand::FButtonCommand()
	: TCommands("ContextName", FText::FromString("ContextDesc"), NAME_None, FEditorStyle::GetStyleSetName())
{
	SpawnVertexCommand = MakeShareable(new FUICommandList());
}

FButtonCommand::~FButtonCommand()
{
	if (SpawnVertexCommand.IsValid())
		SpawnVertexCommand.Reset();
}

void FButtonCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(SpawnVertexButton, "SpawnVertexButton", "Spawn Vertex Button", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenViewerButton, "OpenViewerButton", "Open Viewer Button", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE

	FExecuteAction executeAction = FExecuteAction::CreateRaw(this, &FButtonCommand::SpawnVertexButton_Pressed);
	FExecuteAction executeAction2 = FExecuteAction::CreateRaw(this, &FButtonCommand::OpenViewerButton_Pressed);
	SpawnVertexCommand->MapAction(SpawnVertexButton, executeAction);
	SpawnVertexCommand->MapAction(OpenViewerButton, executeAction2);
}

void FButtonCommand::SpawnVertexButton_Pressed()
{
	//UE_LOG(LogTemp, Error, L"SpawnVertexButton_Pressed");
	/*TArray<const FSlateBrush*> brushes;
	FEditorStyle::GetResources(brushes);

	for (const auto& brush : brushes)
		UE_LOG(LogTemp, Warning, L"%s", *brush->GetResourceName().ToString());*/

//-----------------------------------------------------------------------------------------------------
// @@ Open File Dialog
//-----------------------------------------------------------------------------------------------------
	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();

	FString path;
	TArray<FString> fileNames;
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();
	platform->OpenFileDialog(handle, "Load", path, "", "Binary File(*.bin)|*.bin", EFileDialogFlags::None, fileNames);
	if (fileNames.Num() < 1) return;

	// -> File Archive
	FBufferArchive buffer;
	FFileHelper::LoadFileToArray(buffer, *fileNames[0]);

	// 읽기
	FMemoryReader reader(buffer, true);
	buffer.Seek(0);		// 처음부터 다시 읽기

	FVertexData data;
	reader << data;
	reader.FlushCache();
	reader.Close();

	GLog->Logf(L"Vertex Count : %d", data.Positions.Num());
	GLog->Logf(L"Index Count : %d", data.Indices.Num());

#ifdef TEST_CSV
	// -> Save File(*_opened.csv)
	FString planeText;
	for (int32 i = 0; i < data.Positions.Num(); i++)
	{
		planeText.Append(data.Positions[i].ToString() + ",");
		planeText.Append(data.Normals[i].ToString() + ",");
		planeText.Append(data.UVs[i].ToString() + ",");
		planeText.Append("\n");
	}


	FString PlaneTextPath = FPaths::GetBaseFilename(fileNames[0], false);	// 확장자가 빠진 전체 경로
	PlaneTextPath.Append("_opened.csv");
	FFileHelper::SaveStringToFile(planeText, *PlaneTextPath);
#endif // TEST_CSV

	// Spawn LoadMesh from Binary File
	// 현재 활성화되어있는 viewport들의 기능들을 가져옴
	FLevelEditorViewportClient* viewportClient = (FLevelEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();
	
	// 에디터 상의 world를 가져오는 방법
	UWorld* world = GEditor->GetEditorWorldContext().World();

	FHitResult hitResult;
	FVector start = viewportClient->GetViewLocation();
	FVector end = start + viewportClient->GetViewRotation().RotateVector(FVector(1e+4f, 0, 0));

	world->LineTraceSingleByChannel
	(
		hitResult,
		start,
		end,
		ECollisionChannel::ECC_Visibility
	);

	if (hitResult.bBlockingHit == false)
	{
		UE_LOG(LogTemp, Error, L"Out of Range");
		return;
	}

	FTransform transform;
	transform.SetLocation(hitResult.ImpactPoint);
	FVector direction = (hitResult.TraceEnd - hitResult.TraceStart).GetSafeNormal();
	FRotator rotator = FRotator(0, direction.Rotation().Yaw, 0);
	transform.SetRotation((FQuat)rotator);

	ACLoadMesh* spawnedActor = world->SpawnActorDeferred<ACLoadMesh>
	(
		ACLoadMesh::StaticClass(),
		transform,
		nullptr,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
	);
	spawnedActor->SetPositions(data.Positions);
	spawnedActor->SetIndices(data.Indices);
	spawnedActor->SetNormals(data.Normals);
	spawnedActor->SetUVs(data.UVs);
	spawnedActor->SetColors(data.Colors);

	spawnedActor->FinishSpawning(transform);
}

void FButtonCommand::OpenViewerButton_Pressed()
{
	FMeshViewer::OpenWindow(NewObject<UCDetailAsset>());
}