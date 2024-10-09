// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "CSGAreaComponent.generated.h"

/// @brief The area to perform CSG around, this is a sphere which is active on the provided Collision channel
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CSGAREA_API UCSGAreaComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCSGAreaComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TEnumAsByte<ECollisionChannel> CollisionChannel;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> SphereComponent;
#endif

	virtual void OnRegister() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
};
