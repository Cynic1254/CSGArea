// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSGBaseComponent.h"
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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
