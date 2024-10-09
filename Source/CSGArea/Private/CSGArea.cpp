// Copyright Epic Games, Inc. All Rights Reserved.

#include "CSGArea.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#include "PluginSettings.h"
#endif

#define LOCTEXT_NAMESPACE "FCSGAreaModule"

void FCSGAreaModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#if WITH_EDITOR
	if (ISettingsModule* Settings = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		Settings->RegisterSettings("Project", "Plugins", "CSGArea",
		                           LOCTEXT("RuntimeSettingsName", "CSGArea Settings"),
		                           LOCTEXT("RuntimeSettingsDescription",
		                                   "Collision channel to use for detecting CSG collisions"),
		                           GetMutableDefault<UPluginSettings>());
	}
#endif
}

void FCSGAreaModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "CSGArea");
	}
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCSGAreaModule, CSGArea)
