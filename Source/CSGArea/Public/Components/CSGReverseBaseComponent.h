// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DynamicMeshComponent.h"
#include "GeometryScript/CollisionFunctions.h"
#include "CSGReverseBaseComponent.generated.h"

/// @brief Base component for performing subtractive CSG,
/// To use this component user's should implement the GetVisualMesh and GetCollisionMesh functions
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract)
class CSGAREA_API UCSGReverseBaseComponent : public UDynamicMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCSGReverseBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/// Function used for retrieving the Visual Mesh of the component,
	/// 
	/// @warning This function must be implemented for the class to work
	/// 
	/// @param OutMesh Output dynamic mesh, will be empty when function gets called
	UFUNCTION(BlueprintImplementableEvent)
	void GetVisualMesh(UDynamicMesh* OutMesh);

	/// Function used for retrieving the Collision Mesh of the component,
	/// 
	/// @warning This function must be implemented for the class to work
	/// 
	/// @param OutMesh Output dynamic mesh, will be empty when function gets called
	UFUNCTION(BlueprintImplementableEvent)
	void GetCollisionMesh(UDynamicMesh* OutMesh);

	void RebuildMesh(UDynamicMesh* OutMesh);

	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditAnywhere)
	FGeometryScriptCollisionFromMeshOptions CollisionOptions;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
