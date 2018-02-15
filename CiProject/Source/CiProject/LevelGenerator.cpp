// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenerator.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Runtime/CoreUObject/Public/UObject/Class.h"
#include <time.h>
#include <stdlib.h> 
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
	if (Seed == 0)
	{
		srand(time(0));
	}
	else
	{
		srand(Seed);
	}

	UWorld* world = GetWorld();
	FVector starter(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	int spawnedCounter = 0;
	int first = rand() % Prefabs.Num();
	world->SpawnActor<APrefab>(Prefabs[first], starter, Rotation, SpawnInfo);
	spawnedCounter++;
	if (Prefabs[first]->GetDefaultObject<APrefab>()->leftBoundaryIsConnector)
	{
		SpawnPrefab(starter, Prefabs[first]->GetDefaultObject<APrefab>()->leftBoundary, 'L', spawnedCounter);
	}
	if (Prefabs[first]->GetDefaultObject<APrefab>()->rightBoundaryIsConnector)
	{
		SpawnPrefab(starter, Prefabs[first]->GetDefaultObject<APrefab>()->rightBoundary, 'R', spawnedCounter);
	}
	if (Prefabs[first]->GetDefaultObject<APrefab>()->topBoundaryIsConnector)
	{
		SpawnPrefab(starter, Prefabs[first]->GetDefaultObject<APrefab>()->topBoundary, 'U', spawnedCounter);
	}
	if (Prefabs[first]->GetDefaultObject<APrefab>()->bottomBoundaryIsConnector)
	{
		SpawnPrefab(starter, Prefabs[first]->GetDefaultObject<APrefab>()->bottomBoundary, 'D', spawnedCounter);
	}
}

void ALevelGenerator::SpawnPrefab(FVector locationWorld, FVector locationRelative, char connectorOld, int& spawned)
{
	UWorld* world = GetWorld();
	char connectorNew;
	//Break condition, all spawning has been done
	if (spawned == NumberOfRooms)
	{
		return;
	}
	//Find a valid Prefab to use and work out shift
	bool valid = 0;
	int potential;
	FVector Location = locationWorld;
	while (valid == 0)
	{
		//Get a Prefab (index) then check if it will connect
		potential = rand() % Prefabs.Num();
		if (connectorOld == 'L' && Prefabs[potential]->GetDefaultObject<APrefab>()->rightBoundaryIsConnector)
		{
			valid = 1;
			Location = Location + locationRelative - Prefabs[potential]->GetDefaultObject<APrefab>()->rightBoundary;
			connectorNew = 'R';
		}
		else if (connectorOld == 'R' && Prefabs[potential]->GetDefaultObject<APrefab>()->leftBoundaryIsConnector)
		{
			valid = 1;
			Location = Location + locationRelative - Prefabs[potential]->GetDefaultObject<APrefab>()->leftBoundary;
			connectorNew = 'L';
		}
		else if (connectorOld == 'U' && Prefabs[potential]->GetDefaultObject<APrefab>()->bottomBoundaryIsConnector)
		{
			valid = 1;
			Location = Location + locationRelative - Prefabs[potential]->GetDefaultObject<APrefab>()->bottomBoundary;
			connectorNew = 'D';
		}
		else if (connectorOld == 'D' && Prefabs[potential]->GetDefaultObject<APrefab>()->topBoundaryIsConnector)
		{
			valid = 1;
			Location = Location + locationRelative - Prefabs[potential]->GetDefaultObject<APrefab>()->topBoundary;
			connectorNew = 'U';
		}
	}
	//Spawn it
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	world->SpawnActor<APrefab>(Prefabs[potential], Location, Rotation, SpawnInfo);
	spawned++;
	//Call function for its connectors
	if (connectorNew != 'L')
	{
		if (Prefabs[potential]->GetDefaultObject<APrefab>()->leftBoundaryIsConnector)
		{
			SpawnPrefab(Location, Prefabs[potential]->GetDefaultObject<APrefab>()->leftBoundary, 'L', spawned);
		}
	}
	if (connectorNew != 'R')
	{
		if (Prefabs[potential]->GetDefaultObject<APrefab>()->rightBoundaryIsConnector)
		{
			SpawnPrefab(Location, Prefabs[potential]->GetDefaultObject<APrefab>()->rightBoundary, 'R', spawned);
		}
	}
	if (connectorNew != 'U')
	{
		if (Prefabs[potential]->GetDefaultObject<APrefab>()->topBoundaryIsConnector)
		{
			SpawnPrefab(Location, Prefabs[potential]->GetDefaultObject<APrefab>()->topBoundary, 'U', spawned);
		}
	}
	if (connectorNew != 'D')
	{
		if (Prefabs[potential]->GetDefaultObject<APrefab>()->bottomBoundaryIsConnector)
		{
			SpawnPrefab(Location, Prefabs[potential]->GetDefaultObject<APrefab>()->bottomBoundary, 'D', spawned);
		}
	}
}