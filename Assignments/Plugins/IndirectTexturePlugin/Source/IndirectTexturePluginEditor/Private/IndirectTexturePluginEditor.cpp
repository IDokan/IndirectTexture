// Copyright Epic Games, Inc. All Rights Reserved.

#include "IndirectTexturePluginEditor.h"

#define LOCTEXT_NAMESPACE "FIndirectTexturePluginEditorModule"

void FIndirectTexturePluginEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IndirectTextureAssetTypeActions = MakeShared<FIndirectTextureAssetTypeActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(IndirectTextureAssetTypeActions.ToSharedRef());
}

void FIndirectTexturePluginEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;
	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(IndirectTextureAssetTypeActions.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FIndirectTexturePluginEditorModule, IndirectTexturePluginEditor)