// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicMeshActor.h"
#include "CSGActorBase.generated.h"

UCLASS()
class DUALWORLDS_API ACSGActorBase : public ADynamicMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACSGActorBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// Event to construct the base mesh, this function will get called by the Tick function to get the mesh we will use to apply CSG to
	/// @return Mesh to work with
	UFUNCTION(BlueprintImplementableEvent)
	UDynamicMesh* GetFullMesh();
	UFUNCTION(BlueprintImplementableEvent)
	UDynamicMesh* GetFullCollisionMesh();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool ShouldPerformCSG();

	void LoadSettings();
	
	void RebuildMesh();
	
	UPROPERTY()
	TObjectPtr<UDynamicMeshComponent> Mesh;

	TEnumAsByte<ECollisionChannel> CollisionChannel;
};
