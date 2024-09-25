// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CSGSkeletonComponent.h"

#include "GeometryScript/MeshAssetFunctions.h"
#include "GeometryScript/MeshPrimitiveFunctions.h"


// Sets default values for this component's properties
UCSGSkeletonComponent::UCSGSkeletonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

#if WITH_EDITORONLY_DATA
	if (!IsRunningGame())
	{
		SkeletalMeshPreview = CreateDefaultSubobject<USkeletalMeshComponent>("Preview Mesh");
		SkeletalMeshPreview->SetupAttachment(this);
		SkeletalMeshPreview->SetSkeletalMesh(SkeletonMesh);
		SkeletalMeshPreview->SetHiddenInGame(true);
		SkeletalMeshPreview->bIsEditorOnly = true;

		CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Collision Preview");
		CapsuleComponent->SetupAttachment(this);
		CapsuleComponent->SetCapsuleRadius(CollisionRadius);
		CapsuleComponent->SetCapsuleHalfHeight(HalfHeight);
		CapsuleComponent->SetHiddenInGame(true);
		CapsuleComponent->bIsEditorOnly = true;

		//CapsuleComponent->AddLocalOffset({0, 0, HalfHeight});
	}
#endif
}


// Called when the game starts
void UCSGSkeletonComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UCSGSkeletonComponent::GetVisualMesh_Implementation(UDynamicMesh* OutMesh)
{
	if (!SkeletonMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Skeleton Mesh not set"));
		return;
	}

	EGeometryScriptOutcomePins Success;
	UGeometryScriptLibrary_StaticMeshFunctions::CopyMeshFromSkeletalMesh(SkeletonMesh, OutMesh, {}, {}, Success);
}

void UCSGSkeletonComponent::GetCollisionMesh_Implementation(UDynamicMesh* OutMesh)
{
	UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendCapsule(OutMesh, {}, {}, CollisionRadius, HalfHeight,
	                                                             HemisphereSteps, CircleSteps);
}

void UCSGSkeletonComponent::OnRegister()
{
	Super::OnRegister();

#if WITH_EDITORONLY_DATA
	if (!IsRunningGame())
	{
		SkeletalMeshPreview->SetSkeletalMesh(SkeletonMesh);

		CapsuleComponent->SetCapsuleRadius(CollisionRadius);
		CapsuleComponent->SetCapsuleHalfHeight(HalfHeight);

		CapsuleComponent->AddLocalOffset({0, 0, HalfHeight});
	}
#endif
}

void UCSGSkeletonComponent::OnUnregister()
{
	Super::OnUnregister();

#if WITH_EDITORONLY_DATA
	if (!IsRunningGame())
	{
		SkeletalMeshPreview->DestroyComponent();
		CapsuleComponent->DestroyComponent();
	}
#endif
}

// Called every frame
void UCSGSkeletonComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
