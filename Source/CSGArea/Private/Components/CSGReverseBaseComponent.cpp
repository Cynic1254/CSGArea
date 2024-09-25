// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CSGReverseBaseComponent.h"

#include "PluginSettings.h"
#include "Components/CSGAreaComponent.h"
#include "GeometryScript/MeshBooleanFunctions.h"
#include "GeometryScript/MeshPrimitiveFunctions.h"


// Sets default values for this component's properties
UCSGReverseBaseComponent::UCSGReverseBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	CollisionChannel = GetDefault<UPluginSettings>()->CollisionChannel;

	UCSGReverseBaseComponent::SetCollisionResponseToAllChannels(ECR_Ignore);
	UCSGReverseBaseComponent::SetCollisionResponseToChannel(CollisionChannel, ECR_Overlap);
	UCSGReverseBaseComponent::SetCollisionObjectType(CollisionChannel);
}


// Called when the game starts
void UCSGReverseBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UCSGReverseBaseComponent::RebuildMesh(UDynamicMesh* OutMesh)
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
void UCSGReverseBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TickType == LEVELTICK_All)
	{
		const auto MeshPool = NewObject<UDynamicMeshPool>();
		const auto VisualMesh = MeshPool->RequestMesh();
		GetVisualMesh(VisualMesh);

		RebuildMesh(GetDynamicMesh());

		const auto CollisionMesh = MeshPool->RequestMesh();
		GetCollisionMesh(CollisionMesh);

		RebuildMesh(CollisionMesh);

		UGeometryScriptLibrary_CollisionFunctions::SetDynamicMeshCollisionFromMesh(
			CollisionMesh, this, CollisionOptions);
	}
}
