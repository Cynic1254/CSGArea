// Fill out your copyright notice in the Description page of Project Settings.


#include "actors/CSGActorBase.h"

#include "ISettingsModule.h"
#include "PluginSettings.h"
#include "Components/CSGAreaComponent.h"
#include "GeometryScript/MeshAssetFunctions.h"
#include "GeometryScript/MeshBasicEditFunctions.h"
#include "GeometryScript/MeshBooleanFunctions.h"
#include "GeometryScript/MeshPrimitiveFunctions.h"


// Sets default values
ACSGActorBase::ACSGActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACSGActorBase::BeginPlay()
{
	Super::BeginPlay();
}

bool ACSGActorBase::ShouldPerformCSG()
{
	return true;
}

void ACSGActorBase::LoadSettings()
{
	if (ISettingsModule* Settings = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		CollisionChannel = GetDefault<UPluginSettings>()->CollisionChannel;
	}
}

void ACSGActorBase::RebuildMesh()
{
	TArray<UPrimitiveComponent*> OverlappingComponents;
	GetOverlappingComponents(OverlappingComponents);

	const auto DynamicMesh = DynamicMeshComponent->GetDynamicMesh();
	DynamicMesh->Reset();

	UDynamicMeshPool* MeshPool = NewObject<UDynamicMeshPool>();

	UDynamicMesh* BaseMesh = GetFullMesh();

	TArray<UDynamicMesh*> MeshPieces;

	for (auto OverlappingComponent : OverlappingComponents)
	{
		if (auto* Component = Cast<UCSGAreaComponent>(OverlappingComponent))
		{
			UDynamicMesh* TempMesh = MeshPool->RequestMesh();

			UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendSphereBox(
				TempMesh, {}, Component->GetComponentTransform(), Component->GetUnscaledSphereRadius());

			UGeometryScriptLibrary_MeshBooleanFunctions::ApplyMeshBoolean(
				TempMesh, {},
				BaseMesh, GetTransform(),
				EGeometryScriptBooleanOperation::Intersection,
				{true, true, 0.01, true});

			MeshPieces.Push(TempMesh);
		}
	}

	for (auto Piece : MeshPieces)
	{
		UGeometryScriptLibrary_MeshBooleanFunctions::ApplyMeshBoolean(
			DynamicMesh, GetTransform(),
			Piece, {},
			EGeometryScriptBooleanOperation::Union,
			{true, true, 0.01, true});
	}
}

// Called every frame
void ACSGActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RebuildMesh();
}
