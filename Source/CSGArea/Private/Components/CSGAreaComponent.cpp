// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CSGAreaComponent.h"

#include "PluginSettings.h"


// Sets default values for this component's properties
UCSGAreaComponent::UCSGAreaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	CollisionChannel = GetDefault<UPluginSettings>()->CollisionChannel;

	UCSGAreaComponent::SetCollisionResponseToAllChannels(ECR_Ignore);
	UCSGAreaComponent::SetCollisionResponseToChannel(CollisionChannel, ECR_Overlap);
	UCSGAreaComponent::SetCollisionObjectType(CollisionChannel);

#if WITH_EDITORONLY_DATA
	if (!IsRunningGame())
	{
		SphereComponent = CreateDefaultSubobject<UStaticMeshComponent>("Preview Mesh");
		SphereComponent->SetupAttachment(this);
		SphereComponent->SetStaticMesh(
			ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Sphere.Sphere")).Object);
		SphereComponent->SetHiddenInGame(true);
		SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		SphereComponent->bIsEditorOnly = true;
		SphereComponent->SetMaterial(0, GetDefault<UPluginSettings>()->DefaultAreaMaterial.Get());

		SphereComponent->SetRelativeScale3D(FVector{SphereRadius / 50.0f});
	}

#endif
}


// Called when the game starts
void UCSGAreaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UCSGAreaComponent::OnRegister()
{
	Super::OnRegister();

#if WITH_EDITORONLY_DATA
	if (!IsRunningGame())
	{
		SphereComponent->SetRelativeScale3D(FVector{SphereRadius / 50});
	}
#endif
}

void UCSGAreaComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

#if WITH_EDITORONLY_DATA
	if (!IsRunningGame())
	{
		SphereComponent->DestroyComponent();
	}
#endif
}


// Called every frame
void UCSGAreaComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}
