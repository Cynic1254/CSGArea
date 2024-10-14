// Fill out your copyright notice in the Description page of Project Settings.


#include "Testing/RayTraceComponent.h"

#include "Components/BillboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
URayTraceComponent::URayTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	Start = CreateDefaultSubobject<UBillboardComponent>(TEXT("Start"));
	Start->SetupAttachment(this);

	End = CreateDefaultSubobject<UBillboardComponent>(TEXT("End"));
	End->SetupAttachment(this);
}

bool URayTraceComponent::PerformTrace()
{
	const TArray<AActor*> Actors;
	FHitResult HitResult;
	const bool Result = UKismetSystemLibrary::LineTraceSingle(this, Start->GetComponentLocation(),
	                                                          End->GetComponentLocation(),
	                                                          UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
	                                                          Actors,
	                                                          EDrawDebugTrace::ForDuration, HitResult, false);

	return FailWhenHit ? !Result : Result;
}


// Called when the game starts
void URayTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


void URayTraceComponent::OnRegister()
{
	Super::OnRegister();

	Start->RegisterComponent();
	End->RegisterComponent();
}

// Called every frame
void URayTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
