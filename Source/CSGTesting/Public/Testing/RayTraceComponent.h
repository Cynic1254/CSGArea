// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RayTraceComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CSGTESTING_API URayTraceComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URayTraceComponent();

	bool PerformTrace();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBillboardComponent> Start;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBillboardComponent> End;

	UPROPERTY(EditAnywhere)
	bool FailWhenHit = false;

	virtual void OnRegister() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
