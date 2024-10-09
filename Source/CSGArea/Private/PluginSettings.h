// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/EngineTypes.h"
#include "Materials/MaterialInterface.h"
#include "PluginSettings.generated.h"

/**
 * 
 */
UCLASS(config = "Engine")
class CSGAREA_API UPluginSettings : public UObject
{
	GENERATED_BODY()

public:
	UPluginSettings()
	{
	};

	/// @brief Collision channel to use for detecting CSG collisions
	UPROPERTY(Config, EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_WorldStatic;

	UPROPERTY(Config, EditAnywhere, Category = "Preview")
	TSoftObjectPtr<UMaterialInterface> DefaultAreaMaterial;
};
