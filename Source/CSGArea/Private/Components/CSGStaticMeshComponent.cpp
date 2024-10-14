// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CSGStaticMeshComponent.h"

#include "GeometryScript/MeshAssetFunctions.h"

// Sets default values for this component's properties
UCSGStaticMeshComponent::UCSGStaticMeshComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

#if WITH_EDITORONLY_DATA
	if (!IsRunningGame())
	{
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Preview Mesh");
		MeshComponent->SetupAttachment(this);
		MeshComponent->SetStaticMesh(Mesh);
		MeshComponent->SetCollisionResponseToChannels(UCSGStaticMeshComponent::GetCollisionResponseToChannels());
		MeshComponent->SetHiddenInGame(true);
		MeshComponent->bIsEditorOnly = true;
	}

#endif
}


// Called when the game starts
void UCSGStaticMeshComponent::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITORONLY_DATA
	if (MeshComponent)
	{
		MeshComponent->DestroyComponent();
	}
#endif

	// ...
}

void UCSGStaticMeshComponent::GetVisualMesh_Implementation(UDynamicMesh* OutMesh)
{
	EGeometryScriptOutcomePins Result;
	UGeometryScriptDebug* Debug = NewObject<UGeometryScriptDebug>();
	UGeometryScriptLibrary_StaticMeshFunctions::CopyMeshFromStaticMesh(Mesh, OutMesh, {}, {}, Result, Debug);
}

void UCSGStaticMeshComponent::GetCollisionMesh_Implementation(UDynamicMesh* OutMesh)
{
	EGeometryScriptOutcomePins Result;
	UGeometryScriptDebug* Debug = NewObject<UGeometryScriptDebug>();
	UGeometryScriptLibrary_StaticMeshFunctions::CopyMeshFromStaticMesh(Mesh, OutMesh, {}, {}, Result, Debug);
}

void UCSGStaticMeshComponent::OnRegister()
{
	Super::OnRegister();

#if WITH_EDITORONLY_DATA
	if (!IsRunningGame() && MeshComponent)
	{
		MeshComponent->SetStaticMesh(Mesh);
	}
#endif
}

void UCSGStaticMeshComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
#if WITH_EDITORONLY_DATA
	if (!IsRunningGame() && MeshComponent)
	{
		MeshComponent->DestroyComponent();
	}
#endif
}

// Called every frame
void UCSGStaticMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
