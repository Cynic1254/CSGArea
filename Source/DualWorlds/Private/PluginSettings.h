// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PluginSettings.generated.h"

/**
 * 
 */
UCLASS(config = PluginSettings)
class DUALWORLDS_API UPluginSettings : public UObject
{
	GENERATED_BODY()

public:
	UPluginSettings() {};

	UPROPERTY(Config, EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_WorldStatic;
};
