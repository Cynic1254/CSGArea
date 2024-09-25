// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CSGAreaComponent.h"

#include "PluginSettings.h"


// Sets default values for this component's properties
UCSGAreaComponent::UCSGAreaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CollisionChannel = GetDefault<UPluginSettings>()->CollisionChannel;

	UCSGAreaComponent::SetCollisionResponseToAllChannels(ECR_Ignore);
	UCSGAreaComponent::SetCollisionResponseToChannel(CollisionChannel, ECR_Overlap);
	UCSGAreaComponent::SetCollisionObjectType(CollisionChannel);
}


// Called when the game starts
void UCSGAreaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UCSGAreaComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
