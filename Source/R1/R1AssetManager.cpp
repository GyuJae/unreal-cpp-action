// Fill out your copyright notice in the Description page of Project Settings.
#include "R1AssetManager.h"
#include "R1AssetData.h"
#include "Engine/StreamableManager.h"

UR1AssetManager::UR1AssetManager() : Super()
{
}

UR1AssetManager& UR1AssetManager::Get()
{
    if (UR1AssetManager* Singleton = Cast<UR1AssetManager>(GEngine->AssetManager))
    {
        return *Singleton;
    }
    else
    {
        UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in the GameInstance"));
        return *NewObject<UR1AssetManager>();
    }
}

UObject* UR1AssetManager::LoadSyncByPath(const FSoftObjectPath& AssetPath)
{
    if (!AssetPath.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Asset Path."));
        return nullptr;
    }

    FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
    return Streamable.LoadSynchronous(AssetPath, true);
}

UObject* UR1AssetManager::LoadSyncByName(const FName& AssetName)
{
    if (!LoadAssetData)
    {
        UE_LOG(LogTemp, Warning, TEXT("LoadAssetData is not initialized."));
        return nullptr;
    }

    FSoftObjectPath AssetPath = LoadAssetData->GetAssetPathByName(AssetName);
    return LoadSyncByPath(AssetPath);
}

TArray<UObject*> UR1AssetManager::LoadSyncByLabel(const FName& Label)
{
    if (!LoadAssetData)
    {
        UE_LOG(LogTemp, Warning, TEXT("LoadAssetData is not initialized."));
        return {};
    }

    const FAssetSet& AssetSet = LoadAssetData->GetAssetSetByLabel(Label);
    TArray<UObject*> LoadedAssets;

    for (const FAssetEntry& Entry : AssetSet.AssetEntries)
    {
        UObject* Asset = LoadSyncByPath(Entry.AssetPath);
        if (Asset)
        {
            LoadedAssets.Add(Asset);
        }
    }

    return LoadedAssets;
}

void UR1AssetManager::ReleaseByPath(const FSoftObjectPath& AssetPath)
{
    UObject* Asset = AssetPath.ResolveObject();
    if (Asset)
    {
        Asset->RemoveFromRoot();
        Asset->ConditionalBeginDestroy();
    }
}

void UR1AssetManager::ReleaseByName(const FName& AssetName)
{
    if (UObject* Asset = NameToLoadedAsset.FindRef(AssetName))
    {
        ReleaseByPath(FSoftObjectPath(Asset->GetPathName()));
        NameToLoadedAsset.Remove(AssetName);
    }
}

void UR1AssetManager::ReleaseByLabel(const FName& Label)
{
    if (!LoadAssetData)
    {
        UE_LOG(LogTemp, Warning, TEXT("LoadAssetData is not initialized."));
        return;
    }

    const FAssetSet& AssetSet = LoadAssetData->GetAssetSetByLabel(Label);
    for (const FAssetEntry& Entry : AssetSet.AssetEntries)
    {
        ReleaseByPath(Entry.AssetPath);
    }
}

void UR1AssetManager::ReleaseAll()
{
    for (auto& Pair : NameToLoadedAsset)
    {
        ReleaseByPath(FSoftObjectPath(Pair.Value->GetPathName()));
    }

    NameToLoadedAsset.Empty();
}

void UR1AssetManager::Initialize()
{
    if (!GEngine->AssetManager)
    {
        UR1AssetManager* AssetManager = NewObject<UR1AssetManager>();
        AssetManager->SetFlags(RF_Standalone);
        AssetManager->AddToRoot();
        GEngine->AssetManager = AssetManager;
    }
}