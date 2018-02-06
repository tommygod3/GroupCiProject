// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenerator.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
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
	if (PF1)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FVector Location(0.0f, 0.0f, 0.0f);
			FRotator Rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnInfo;
			world->SpawnActor<AStaticMeshActor>(PF1, Location, Rotation, SpawnInfo);
		}
	}
	if (PF2)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FVector Location(717.0f, 0.0f, 0.0f);
			FRotator Rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnInfo;
			world->SpawnActor<AStaticMeshActor>(PF2, Location, Rotation, SpawnInfo);
		}
	}
}