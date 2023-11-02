#include "RHI/CButtonActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACButtonActor::ACButtonActor()
{
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");

	UStaticMesh* meshAsset;
	CHelpers::GetAsset<UStaticMesh>(&meshAsset, "StaticMesh'/Game/StaticMeshes/SM_Merged.SM_Merged'");

	UMaterialInstanceConstant* materialAsset;
	CHelpers::GetAsset<UMaterialInstanceConstant>(&materialAsset, "MaterialInstanceConstant'/Game/Materials/Surface/MI_Shffle.MI_Shffle'");

	Mesh->SetStaticMesh(meshAsset);
	Mesh->SetMaterial(0, materialAsset);
}

void ACButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
}
