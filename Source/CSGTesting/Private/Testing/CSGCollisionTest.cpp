// Fill out your copyright notice in the Description page of Project Settings.


#include "Testing/CSGCollisionTest.h"

#include "Testing/RayTraceComponent.h"

ACSGCollisionTest::ACSGCollisionTest()
{
}

void ACSGCollisionTest::StartTest()
{
	Super::StartTest();

	TArray<URayTraceComponent*> FailedTraces;

	for (const auto Component : GetComponents())
	{
		if (auto RayTraceComponent = Cast<URayTraceComponent>(Component))
		{
			AddInfo(FString{"Performing Test for: "} + RayTraceComponent->GetName());
			if (!RayTraceComponent->PerformTrace())
			{
				AddWarning(FString{"Failed"});
				FailedTraces.Add(RayTraceComponent);
			}
			else
			{
				AddInfo(FString{"Succeeded"});
			}
		}
	}

	if (FailedTraces.Num() != 0)
	{
		FString Message = "Failed Tests: ";
		for (auto Fail : FailedTraces)
		{
			Message += Fail->GetName() + ", ";
		}

		FinishTest(EFunctionalTestResult::Failed, Message);
	}
	else
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString{"All Tests Succeeded"});
	}
}

void ACSGCollisionTest::PrepareTest()
{
	Super::PrepareTest();
}

void ACSGCollisionTest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
