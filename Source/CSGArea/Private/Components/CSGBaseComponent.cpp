// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CSGBaseComponent.h"

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
}

// Called when the game starts
void UCSGBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	int i = 0;
	for (; i < Materials.Num(); ++i)
	{
		SetMaterial(i, Materials[i]);
	}
	SetMaterial(i, CSGMaterial);

	MarkRenderStateDirty();

	MeshPool = NewObject<UDynamicMeshPool>(this);
}


void UCSGBaseComponent::RebuildMesh(UDynamicMesh* OutMesh, UDynamicMesh* FullMesh) const
{
	const auto DynamicMesh = OutMesh;

	TArray<UPrimitiveComponent*> Overlapping;
	GetOwner()->GetOverlappingComponents(Overlapping);

	UDynamicMesh* BaseMesh = FullMesh;

	TArray<UDynamicMesh*> MeshPieces;

	for (const auto OverlappingComponent : Overlapping)
	{
		if (const auto* Component = Cast<UCSGAreaComponent>(OverlappingComponent))
		{
			UDynamicMesh* TempMesh = MeshPool->RequestMesh();

			UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendSphereBox(
				TempMesh, {}, Component->GetComponentTransform(), Component->GetUnscaledSphereRadius());

			int MaterialIndex = Materials.Num();
			TempMesh->EditMesh([MaterialIndex](FDynamicMesh3& Mesh)
			{
				// ReSharper disable once CppTooWideScope
				const auto Material = Mesh.Attributes()->GetMaterialID();

				if (Material)
				{
					for (const auto Triangle : Mesh.TriangleIndicesItr())
					{
						Material->SetValue(Triangle, MaterialIndex);
					}
				}
			});

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

	for (const auto Piece : MeshPieces)
	{
		UGeometryScriptLibrary_MeshBooleanFunctions::ApplyMeshBoolean(
			DynamicMesh, GetComponentTransform(),
			Piece, {},
			EGeometryScriptBooleanOperation::Union,
			{true, true, 0.01, true});
	}
}

void UCSGBaseComponent::ReverseRebuildMesh(UDynamicMesh* OutMesh) const
{
	TArray<UPrimitiveComponent*> Overlapping;
	GetOwner()->GetOverlappingComponents(Overlapping);

	for (const auto OverlappingComponent : Overlapping)
	{
		if (const auto Component = Cast<UCSGAreaComponent>(OverlappingComponent))
		{
			UDynamicMesh* TempMesh = MeshPool->RequestMesh();

			UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendSphereBox(
				TempMesh, {}, Component->GetComponentTransform(), Component->GetUnscaledSphereRadius());

			int MaterialIndex = Materials.Num();
			TempMesh->EditMesh([MaterialIndex](FDynamicMesh3& Mesh)
			{
				// ReSharper disable once CppTooWideScope
				const auto Material = Mesh.Attributes()->GetMaterialID();

				if (Material)
				{
					for (const auto Triangle : Mesh.TriangleIndicesItr())
					{
						Material->SetValue(Triangle, MaterialIndex);
					}
				}
			});

			UGeometryScriptLibrary_MeshBooleanFunctions::ApplyMeshBoolean(
				OutMesh, GetComponentTransform(),
				TempMesh, {},
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

	if (TickType == LEVELTICK_All)
	{
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

	MeshPool->ReturnAllMeshes();
}
