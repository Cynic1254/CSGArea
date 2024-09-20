// Copyright Epic Games, Inc. All Rights Reserved.

#include "DualWorlds.h"

#include "ISettingsModule.h"
#include "PluginSettings.h"

#define LOCTEXT_NAMESPACE "FDualWorldsModule"

void FDualWorldsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	if (ISettingsModule* Settings = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		Settings->RegisterSettings("Project", "Plugins", "DualWorlds",
			LOCTEXT("RuntimeSettingsName", "My Setting Page"),
			LOCTEXT("RuntimeSettingsDescription", "Configure my setting"),
			GetMutableDefault<UPluginSettings>());

	}
}

void FDualWorldsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "DualWorlds");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDualWorldsModule, DualWorlds)