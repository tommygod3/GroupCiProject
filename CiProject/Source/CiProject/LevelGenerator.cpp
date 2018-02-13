// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenerator.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Runtime/CoreUObject/Public/UObject/Class.h"
#include "Runtime/Engine/Classes/Engine/World.h"


// Sets default values
ALevelGenerator::ALevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	
	ALevelGenerator::Spawn();
}

void ALevelGenerator::Spawn()
{
	if (Prefabs[0]!=nullptr)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FVector Location(0.0f, 0.0f, 0.0f);
			FRotator Rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnInfo;
			world->SpawnActor<APrefab>(Prefabs[0], Location, Rotation, SpawnInfo);
			for (int i = 1; i < Prefabs.Num(); i++)
			{
				Location = Location + Prefabs[i-1]->GetDefaultObject<APrefab>()->rightBoundary - Prefabs[i]->GetDefaultObject<APrefab>()->leftBoundary;
				world->SpawnActor<APrefab>(Prefabs[i], Location, Rotation, SpawnInfo);
			}
		}
	}
}