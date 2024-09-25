// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DynamicMeshComponent.h"
#include "GeometryScript/CollisionFunctions.h"
#include "CSGBaseComponent.generated.h"

/// @brief Base component for performing intersecting CSG,
/// To use this component user's should implement the GetVisualMesh and GetCollisionMesh functions
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class CSGAREA_API UCSGBaseComponent : public UDynamicMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCSGBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/// Function used for retrieving the Visual Mesh of the component,
	/// 
	/// @warning This function must be implemented for the class to work
	/// 
	/// @param OutMesh Output dynamic mesh, will be empty when function gets called
	UFUNCTION(BlueprintNativeEvent)
	void GetVisualMesh(UDynamicMesh* OutMesh);

	/// Function used for retrieving the Collision Mesh of the component,
	/// 
	/// @warning This function must be implemented for the class to work
	/// 
	/// @param OutMesh Output dynamic mesh, will be empty when function gets called
	UFUNCTION(BlueprintNativeEvent)
	void GetCollisionMesh(UDynamicMesh* OutMesh);

	void RebuildMesh(UDynamicMesh* OutMesh, UDynamicMesh* FullMesh);

	void ReverseRebuildMesh(UDynamicMesh* OutMesh);

	TEnumAsByte<ECollisionChannel> CollisionChannel;

	/// @brief Collision options to use when constructing the collision shape
	UPROPERTY(EditAnywhere)
	FGeometryScriptCollisionFromMeshOptions CollisionOptions;

	/// @brief Whether CSG should be based on intersection or subtractive
	/// False means CSG will be based on Intersection
	UPROPERTY(EditAnywhere)
	bool bDoReverseCSG = false;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void GetVisualMesh_Implementation(UDynamicMesh* OutMesh)
	{
		unimplemented();
	}

	virtual void GetCollisionMesh_Implementation(UDynamicMesh* OutMesh)
	{
		unimplemented();
	}
};
