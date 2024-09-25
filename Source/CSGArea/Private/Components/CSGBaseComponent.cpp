// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CSGBaseComponent.h"

#include "PluginSettings.h"
#include "Components/CSGAreaComponent.h"
#include "GeometryScript/CollisionFunctions.h"
#include "GeometryScript/MeshBooleanFunctions.h"
#include "GeometryScript/MeshPrimitiveFunctions.h"


// Sets default values for this component's properties
UCSGBaseComponent::UCSGBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	CollisionChannel = GetDefault<UPluginSettings>()->CollisionChannel;

	UCSGBaseComponent::SetCollisionResponseToAllChannels(ECR_Ignore);
	UCSGBaseComponent::SetCollisionResponseToChannel(CollisionChannel, ECR_Overlap);
	UCSGBaseComponent::SetCollisionObjectType(CollisionChannel);
}


// Called when the game starts
void UCSGBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


void UCSGBaseComponent::RebuildMesh(UDynamicMesh* OutMesh, UDynamicMesh* FullMesh)
{
	const auto DynamicMesh = OutMesh;

	TArray<UPrimitiveComponent*> Overlapping;
	GetOwner()->GetOverlappingComponents(Overlapping);

	UDynamicMeshPool* MeshPool = NewObject<UDynamicMeshPool>();

	UDynamicMesh* BaseMesh = FullMesh;

	TArray<UDynamicMesh*> MeshPieces;

	UE_LOG(LogTemp, Log, TEXT("Rebuilding mesh: %i"), Overlapping.Num());

	for (auto OverlappingComponent : Overlapping)
	{
		if (auto* Component = Cast<UCSGAreaComponent>(OverlappingComponent))
		{
			UDynamicMesh* TempMesh = MeshPool->RequestMesh();

			UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendSphereBox(
				TempMesh, {}, Component->GetComponentTransform(), Component->GetUnscaledSphereRadius());

			UGeometryScriptLibrary_MeshBooleanFunctions::ApplyMeshBoolean(
				TempMesh, {},
				BaseMesh, GetComponentTransform(),
				EGeometryScriptBooleanOperation::Intersection,
				{true, true, 0.01, true});

			MeshPieces.Push(TempMesh);
		}
	}

	//only reset the dynamic mesh now since the OutMesh might also be used for FullMesh
	DynamicMesh->Reset();

	for (auto Piece : MeshPieces)
	{
		UGeometryScriptLibrary_MeshBooleanFunctions::ApplyMeshBoolean(
			DynamicMesh, GetComponentTransform(),
			Piece, {},
			EGeometryScriptBooleanOperation::Union,
			{true, true, 0.01, true});
	}
}

void UCSGBaseComponent::ReverseRebuildMesh(UDynamicMesh* OutMesh)
{
	TArray<UPrimitiveComponent*> Overlapping;
	GetOwner()->GetOverlappingComponents(Overlapping);

	const auto MeshPool = NewObject<UDynamicMeshPool>();

	for (const auto OverlappingComponent : Overlapping)
	{
		if (const auto Component = Cast<UCSGAreaComponent>(OverlappingComponent))
		{
			UDynamicMesh* TempMesh = MeshPool->RequestMesh();

			UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendSphereBox(
				TempMesh, {}, Component->GetComponentTransform(), Component->GetUnscaledSphereRadius());

			UGeometryScriptLibrary_MeshBooleanFunctions::ApplyMeshBoolean(
				OutMesh, {},
				TempMesh, GetComponentTransform(),
				EGeometryScriptBooleanOperation::Subtract,
				{true, true, 0.01, true});
		}
	}
}

// Called every frame
void UCSGBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (TickType == LEVELTICK_All)
	{
		const auto MeshPool = NewObject<UDynamicMeshPool>();

		const auto CollisionMesh = MeshPool->RequestMesh();
		GetCollisionMesh(CollisionMesh);

		if (bDoReverseCSG)
		{
			GetVisualMesh(GetDynamicMesh()->Reset());

			ReverseRebuildMesh(GetDynamicMesh());

			ReverseRebuildMesh(CollisionMesh);
		}
		else
		{
			const auto VisualMesh = MeshPool->RequestMesh();
			GetVisualMesh(VisualMesh);

			RebuildMesh(GetDynamicMesh(), VisualMesh);

			RebuildMesh(CollisionMesh, CollisionMesh);
		}

		UGeometryScriptLibrary_CollisionFunctions::SetDynamicMeshCollisionFromMesh(
			CollisionMesh, this, CollisionOptions);
	}
}

