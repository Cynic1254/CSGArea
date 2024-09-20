// Fill out your copyright notice in the Description page of Project Settings.


#include "actors/CSGActorBase.h"

#include "ISettingsModule.h"
#include "PluginSettings.h"
#include "Components/CSGAreaComponent.h"
#include "GeometryScript/MeshAssetFunctions.h"
#include "GeometryScript/MeshBasicEditFunctions.h"
#include "GeometryScript/MeshPrimitiveFunctions.h"


// Sets default values
ACSGActorBase::ACSGActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UDynamicMeshComponent>("Mesh");
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

	auto DynamicMesh = Mesh->GetDynamicMesh();

	UDynamicMeshPool* MeshPool = NewObject<UDynamicMeshPool>();

	UDynamicMesh* BaseMesh = GetFullMesh();

	TArray<UDynamicMesh> MeshPieces;
	
	for (auto OverlappingComponent : OverlappingComponents)
	{
		if (auto* Component = Cast<UCSGAreaComponent>(OverlappingComponent))
		{
			UDynamicMesh* TempMesh = MeshPool->RequestMesh();

			FGeometryScriptPrimitiveOptions options{
				
			};
			
			//UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendSphereBox(TempMesh, {}, )
		}
	}
}

// Called every frame
void ACSGActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RebuildMesh();
}

