// Fill out your copyright notice in the Description page of Project Settings.
#include "R1AssetManager.h"

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
