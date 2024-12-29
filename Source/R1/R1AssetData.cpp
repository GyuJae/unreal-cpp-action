#include "R1AssetData.h"
#include "UObject/ObjectSaveContext.h"

void UR1AssetData::PreSave(FObjectPreSaveContext ObjectSaveContext)
{
    Super::PreSave(ObjectSaveContext);
    InitializeMappings();
}

void UR1AssetData::InitializeMappings()
{
    AssetNameToPath.Empty();
    AssetLabelToSet.Empty();

    for (const auto& Pair : AssetGroupNameToSet)
    {
        const FAssetSet& AssetSet = Pair.Value;
        for (const FAssetEntry& Entry : AssetSet.AssetEntries)
        {
            // Map AssetName to AssetPath
            if (!Entry.AssetName.IsNone() && Entry.AssetPath.IsValid())
            {
                AssetNameToPath.Add(Entry.AssetName, Entry.AssetPath);
            }

            // Map AssetLabels to AssetSet
            for (const FName& Label : Entry.AssetLabels)
            {
                FAssetSet& LabelSet = AssetLabelToSet.FindOrAdd(Label);
                LabelSet.AssetEntries.Add(Entry);
            }
        }
    }
}

FSoftObjectPath UR1AssetData::GetAssetPathByName(const FName& AssetName) const
{
    const FSoftObjectPath* AssetPath = AssetNameToPath.Find(AssetName);
    ensureAlwaysMsgf(AssetPath, TEXT("Asset with name %s not found"), *AssetName.ToString());
    return AssetPath ? *AssetPath : FSoftObjectPath();
}

const FAssetSet& UR1AssetData::GetAssetSetByLabel(const FName& Label) const
{
    const FAssetSet* AssetSet = AssetLabelToSet.Find(Label);
    ensureAlwaysMsgf(AssetSet, TEXT("Asset set with label %s not found"), *Label.ToString());
    static const FAssetSet EmptySet;
    return AssetSet ? *AssetSet : EmptySet;
}
