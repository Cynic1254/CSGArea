// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSGBaseComponent.h"
#include "CSGStaticMeshComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CSGAREA_API UCSGStaticMeshComponent : public UCSGBaseComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCSGStaticMeshComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetVisualMesh_Implementation(UDynamicMesh* OutMesh) override;
	virtual void GetCollisionMesh_Implementation(UDynamicMesh* OutMesh) override;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMesh> Mesh;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> MeshComponent;
#endif

	virtual void OnRegister() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
