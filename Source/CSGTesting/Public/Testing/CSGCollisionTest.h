// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "CSGCollisionTest.generated.h"

/**
 * 
 */
UCLASS()
class CSGTESTING_API ACSGCollisionTest : public AFunctionalTest
{
	GENERATED_BODY()

public:
	ACSGCollisionTest();

protected:
	UPROPERTY()
	TArray<TObjectPtr<USceneComponent>> RootComponents;

	virtual void StartTest() override;
	virtual void PrepareTest() override;

public:
	virtual void Tick(float DeltaSeconds) override;
};
