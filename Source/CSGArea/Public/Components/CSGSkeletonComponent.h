// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSGBaseComponent.h"
#include "Components/CapsuleComponent.h"
#include "CSGSkeletonComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CSGAREA_API UCSGSkeletonComponent : public UCSGBaseComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCSGSkeletonComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetVisualMesh_Implementation(UDynamicMesh* OutMesh) override;
	virtual void GetCollisionMesh_Implementation(UDynamicMesh* OutMesh) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh | Visual")
	TObjectPtr<USkeletalMesh> SkeletonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh | Collision")
	float CollisionRadius = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh | Collision")
	float HalfHeight = 75;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh | Collision")
	int32 HemisphereSteps = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh | Collision")
	int32 CircleSteps = 8;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshPreview;

	UPROPERTY()
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
#endif

	virtual void OnRegister() override;
	virtual void OnUnregister() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
