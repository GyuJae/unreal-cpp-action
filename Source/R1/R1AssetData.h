// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "R1AssetData.generated.h"

USTRUCT(BlueprintType)
struct FAssetEntry
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Asset")
    FName AssetName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Asset")
    FSoftObjectPath AssetPath;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Asset")
    TArray<FName> AssetLabels;
};

USTRUCT(BlueprintType)
struct FAssetSet
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Asset")
    TArray<FAssetEntry> AssetEntries;
};

/**
 * Primary Data Asset for managing asset sets
 */
UCLASS(BlueprintType)
class R1_API UR1AssetData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public: 
    virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;

    UFUNCTION(BlueprintCallable, Category="Asset Management")
    FSoftObjectPath GetAssetPathByName(const FName& AssetName) const;

    UFUNCTION(BlueprintCallable, Category="Asset Management")
    const FAssetSet& GetAssetSetByLabel(const FName& Label) const;

private:
    void InitializeMappings();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Asset", meta=(AllowPrivateAccess="true"))
    TMap<FName, FAssetSet> AssetGroupNameToSet;

    UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
    TMap<FName, FSoftObjectPath> AssetNameToPath;

    UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
    TMap<FName, FAssetSet> AssetLabelToSet;
};
