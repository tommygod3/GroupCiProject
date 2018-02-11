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
	
	FVector Shifter = Prefabs[0]->GetDefaultObject<APrefab>()->rightConnector - Prefabs[0]->GetDefaultObject<APrefab>()->leftConnector;
	//FVector Shifter(580.0f, 0.0f, 0.0f);
	if (Prefabs[0]!=nullptr)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FVector Location(0.0f, 0.0f, 0.0f);
			FRotator Rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnInfo;
			for (int i = 0; i < NumberOfRooms; i++)
			{
				FVector Shift = Shifter * (i);
				world->SpawnActor<APrefab>(Prefabs[0], Location + (Shift), Rotation, SpawnInfo);
			}
		}
	}
}