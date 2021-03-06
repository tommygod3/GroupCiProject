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
	//Return if we want 0 rooms or have no prefabs
	if (NumberOfRooms == 0 || Prefabs.Num() == 0)
	{
		return;
	}
	//Also return if we are requesting too many gems or spikes (can only have 2 per room)
	if ( NumberOfSpikes > 2* NumberOfRooms || NumberOfGems > 2* NumberOfRooms)
	{
		return;
	}
	//If seed selected as 0, seed randomly
	if (Seed == 0)
	{
		srand(time(0));
	}
	//If not use given
	else
	{
		srand(Seed);
	}
	//Make world and spawn set up for right in the centre
	UWorld* world = GetWorld();
	FVector starter(0.0f, 0.0f, 0.0f);
	//Start spawning first prefab
	toBeSpawned++;
	int first = 0;
	while (true)
	{
		//Keep checking for valid prefab
		first = rand() % Prefabs.Num();
		if (validatePrefab(first))
		{
			break;
		}
	}
	//Spawn it
	worldSpawnPrefab(first, starter, world);
	//Add currently spawning for all its connectors
	toBeSpawned += (noOfConnectors(first));
	//Call spawning function on all of the first prefabs connectors
	if (Prefabs[first]->GetDefaultObject<APrefab>()->leftBoundaryIsConnector)
	{
		SpawnPrefab(starter, Prefabs[first]->GetDefaultObject<APrefab>()->leftBoundary, 'L');
	}
	if (Prefabs[first]->GetDefaultObject<APrefab>()->rightBoundaryIsConnector)
	{
		SpawnPrefab(starter, Prefabs[first]->GetDefaultObject<APrefab>()->rightBoundary, 'R');
	}
	if (Prefabs[first]->GetDefaultObject<APrefab>()->topBoundaryIsConnector)
	{
		SpawnPrefab(starter, Prefabs[first]->GetDefaultObject<APrefab>()->topBoundary, 'U');
	}
	if (Prefabs[first]->GetDefaultObject<APrefab>()->bottomBoundaryIsConnector)
	{
		SpawnPrefab(starter, Prefabs[first]->GetDefaultObject<APrefab>()->bottomBoundary, 'D');
	}
}

void ALevelGenerator::SpawnPrefab(FVector locationWorld, FVector locationRelative, char connectorOld)
{
	UWorld* world = GetWorld();
	char connectorNew;
	//Break condition, all spawning has been done
	if (spawned == NumberOfRooms)
	{
		return;
	}
	//Find a valid Prefab to use and work out shift
	int potential;
	FVector potentialLocation = locationRelative + locationWorld;
	FworldSpace mySpace;

	while (true)
	{
		//Get a Prefab (index) 
		potential = rand() % Prefabs.Num();

		//Check that the prefab won't end the level too early or too late
		if (!validatePrefab(potential))
		{
			continue;
		}

		//Check if the prefab will be blocked by another
		bool blocked = 0;
		//Set my space that I take up
		mySpace = getSpace(potential, potentialLocation);
		for (FworldSpace& blockedSpace : spaces)
		{
			if ((mySpace.downSpace.X > blockedSpace.leftSpace.X && mySpace.downSpace.X < blockedSpace.rightSpace.X) && (mySpace.downSpace.Z > blockedSpace.downSpace.Z && mySpace.downSpace.Z < blockedSpace.upSpace.Z))
			{
				blocked = 1;
			}
			else if ((mySpace.leftSpace.X > blockedSpace.leftSpace.X && mySpace.leftSpace.X < blockedSpace.rightSpace.X) && (mySpace.leftSpace.Z > blockedSpace.downSpace.Z && mySpace.leftSpace.Z < blockedSpace.upSpace.Z))
			{
				blocked = 1;
			}
			else if ((mySpace.rightSpace.X > blockedSpace.leftSpace.X && mySpace.rightSpace.X < blockedSpace.rightSpace.X) && (mySpace.rightSpace.Z > blockedSpace.downSpace.Z && mySpace.rightSpace.Z < blockedSpace.upSpace.Z))
			{
				blocked = 1;
			}
			else if ((mySpace.upSpace.X > blockedSpace.leftSpace.X && mySpace.upSpace.X < blockedSpace.rightSpace.X) && (mySpace.upSpace.Z > blockedSpace.downSpace.Z && mySpace.upSpace.Z < blockedSpace.upSpace.Z))
			{
				blocked = 1;
			}
		}
		if (blocked)
		{
			//continue;
		}
		//Make sure prefab has connector it is coming out of
		if (connectorOld == 'L' && Prefabs[potential]->GetDefaultObject<APrefab>()->rightBoundaryIsConnector)
		{
			potentialLocation -= Prefabs[potential]->GetDefaultObject<APrefab>()->rightBoundary;
			connectorNew = 'R';
			break;
		}
		else if (connectorOld == 'R' && Prefabs[potential]->GetDefaultObject<APrefab>()->leftBoundaryIsConnector)
		{
			potentialLocation -= Prefabs[potential]->GetDefaultObject<APrefab>()->leftBoundary;
			connectorNew = 'L';
			break;
		}
		else if (connectorOld == 'U' && Prefabs[potential]->GetDefaultObject<APrefab>()->bottomBoundaryIsConnector)
		{
			potentialLocation -= Prefabs[potential]->GetDefaultObject<APrefab>()->bottomBoundary;
			connectorNew = 'D';
			break;
		}
		else if (connectorOld == 'D' && Prefabs[potential]->GetDefaultObject<APrefab>()->topBoundaryIsConnector)
		{
			potentialLocation -= Prefabs[potential]->GetDefaultObject<APrefab>()->topBoundary;
			connectorNew = 'U';
			break;
		}
	}
	//Spawn it
	worldSpawnPrefab(potential, potentialLocation, world);
	
	//Add to blocked space
	spaces.Add(mySpace);
	//Add ongoing to counter
	toBeSpawned += (noOfConnectors(potential) - 1);
	//Call function for its connectors
	if (connectorNew != 'L')
	{
		if (Prefabs[potential]->GetDefaultObject<APrefab>()->leftBoundaryIsConnector)
		{
			SpawnPrefab(potentialLocation, Prefabs[potential]->GetDefaultObject<APrefab>()->leftBoundary, 'L');
		}
	}
	if (connectorNew != 'R')
	{
		if (Prefabs[potential]->GetDefaultObject<APrefab>()->rightBoundaryIsConnector)
		{
			SpawnPrefab(potentialLocation, Prefabs[potential]->GetDefaultObject<APrefab>()->rightBoundary, 'R');
		}
	}
	if (connectorNew != 'U')
	{
		if (Prefabs[potential]->GetDefaultObject<APrefab>()->topBoundaryIsConnector)
		{
			SpawnPrefab(potentialLocation, Prefabs[potential]->GetDefaultObject<APrefab>()->topBoundary, 'U');
		}
	}
	if (connectorNew != 'D')
	{
		if (Prefabs[potential]->GetDefaultObject<APrefab>()->bottomBoundaryIsConnector)
		{
			SpawnPrefab(potentialLocation, Prefabs[potential]->GetDefaultObject<APrefab>()->bottomBoundary, 'D');
		}
	}
}

void ALevelGenerator::worldSpawnPrefab(unsigned int prefabNo, FVector location, UWorld* world)
{
	//Spawn the actual prefab given the index on list, location and world
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	world->SpawnActor<APrefab>(Prefabs[prefabNo], location, Rotation, SpawnInfo);

	//Choose how many gems and spikes to spawn
	//1.2 gems
	if (NumberOfGems > gemsSpawned)
	{
		if (2 * (NumberOfRooms - spawned) > (NumberOfGems-gemsSpawned+1))
		{
			if (NumberOfGems - gemsSpawned == 1)
			{
				if (NumberOfRooms - spawned == 1)
				{
					worldSpawnGems(prefabNo, 1, location, world);
				}
			}
			else
			{
				int decider = rand() % 100 + 1;
				if (decider <= 20)
				{

				}
				else if (decider <= 60)
				{
					worldSpawnGems(prefabNo, 1, location, world);
				}
				else
				{
					worldSpawnGems(prefabNo, 2, location, world);
				}
			}
			
		}
		else
		{
			if (2 * (NumberOfRooms - spawned) <= (NumberOfGems - gemsSpawned))
			{
				worldSpawnGems(prefabNo, 2, location, world);
			}
			else
			{
				worldSpawnGems(prefabNo, 1, location, world);
			}
		}
	}
	//1.55 spikes
	if (NumberOfSpikes > spikesSpawned)
	{
		if (2 * (NumberOfRooms-spawned) >= NumberOfSpikes)
		{
			int decider = rand() % 100 + 1;
			if (decider <= 5)
			{

			}
			else if (decider <= 40)
			{
				worldSpawnSpikes(prefabNo, 1, location, world);
			}
			else
			{
				if (NumberOfSpikes - spikesSpawned == 1)
				{
					worldSpawnSpikes(prefabNo, 1, location, world);
				}
				else
				{
					worldSpawnSpikes(prefabNo, 2, location, world);
				}
			}
		}
		else
		{
			worldSpawnSpikes(prefabNo, 2, location, world);
		}
	}
	//Increment number spawned and decrement number of prefabs in spawning process
	spawned++;
	toBeSpawned--;
}

void ALevelGenerator::worldSpawnGems(unsigned int prefabNo, unsigned int numOfGems, FVector location, UWorld* world)
{
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	if (numOfGems == 0)
	{
		return;
	}
	else if (numOfGems == 1)
	{
		unsigned int gemNum = rand() % 2;
		if (gemNum == 0)
		{
			FVector gemLocation = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->potentialGem1.GetLocation() + location;
			world->SpawnActor<AActor>(gemBP, gemLocation, Rotation, SpawnInfo);
		}
		else
		{
			FVector gemLocation = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->potentialGem2.GetLocation() + location;
			world->SpawnActor<AActor>(gemBP, gemLocation, Rotation, SpawnInfo);
		}
		gemsSpawned++;
	}
	else if (numOfGems == 2)
	{
		FVector gemLocation = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->potentialGem1.GetLocation() + location;
		world->SpawnActor<AActor>(gemBP, gemLocation, Rotation, SpawnInfo);

		FVector gemLocationSecond = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->potentialGem2.GetLocation() + location;
		world->SpawnActor<AActor>(gemBP, gemLocationSecond, Rotation, SpawnInfo);
		gemsSpawned++;
		gemsSpawned++;
	}
	else
	{
		return;
	}

}

void ALevelGenerator::worldSpawnSpikes(unsigned int prefabNo, unsigned int numOfSpikes, FVector location, UWorld* world)
{
	FActorSpawnParameters SpawnInfo;
	if (numOfSpikes == 0)
	{
		return;
	}
	else if (numOfSpikes == 1)
	{
		unsigned int spikeNum = rand() % 2;
		if (spikeNum == 0)
		{
			FVector spikeLocation = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->potentialSpike1.GetLocation() + location;
			FRotator spikeRotation = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->potentialSpike1.GetRotation().Rotator();
			world->SpawnActor<AActor>(spikeBP, spikeLocation, spikeRotation, SpawnInfo);
		}
		else
		{
			FVector spikeLocation = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->potentialSpike2.GetLocation() + location;
			FRotator spikeRotation = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->potentialSpike2.GetRotation().Rotator();
			world->SpawnActor<AActor>(spikeBP, spikeLocation, spikeRotation, SpawnInfo);
		}
		spikesSpawned++;
	}
	else if (numOfSpikes == 2)
	{
		FVector spikeLocation = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->potentialSpike1.GetLocation() + location;
		FRotator spikeRotation = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->potentialSpike1.GetRotation().Rotator();
		world->SpawnActor<AActor>(spikeBP, spikeLocation, spikeRotation, SpawnInfo);

		FVector spikeLocationSecond = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->potentialSpike2.GetLocation() + location;
		FRotator spikeRotationSecond = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->potentialSpike2.GetRotation().Rotator();
		world->SpawnActor<AActor>(spikeBP, spikeLocationSecond, spikeRotationSecond, SpawnInfo);

		spikesSpawned++;
		spikesSpawned++;
	}
	else
	{
		return;
	}
}

unsigned int ALevelGenerator::noOfConnectors(unsigned int prefabNo)
{
	//Returns the prefabs number of connectors given index
	return Prefabs[prefabNo]->GetDefaultObject<APrefab>()->noOfConnectors();
}

bool ALevelGenerator::validatePrefab(unsigned int prefabNo)
{
	//Check that prefab is valid

	//If this is the first spawned
	if (spawned == 0)
	{
		//Cannot have more connectors than rooms target
		if (1 + noOfConnectors(prefabNo) > NumberOfRooms)
		{
			return false;
		}
		//Cannot have 0 connectors
		if (noOfConnectors(prefabNo) < 1)
		{
			return false;
		}
	}
	//If this is not the first spawned
	else
	{
		//If this is the last one currently spawning
		if (toBeSpawned == 1)
		{
			//And we aren't hitting our target with the last one
			if (toBeSpawned + spawned != NumberOfRooms)
			{
				//This must have more than 2 connectors so we keep going
				if (noOfConnectors(prefabNo) < 2)
				{
					return false;
				}
			}
			
		}
		//If spawning this will mean we go over the target we can't choose it
		if (spawned + toBeSpawned + noOfConnectors(prefabNo) - 1 > NumberOfRooms)
		{
			return false;
		}
	}
	return true;
}

FworldSpace ALevelGenerator::getSpace(unsigned int prefabNo, FVector relativeLocation)
{
	//Given a prefab number and its relative location, get the world space it takes up
	FworldSpace mySpace;
	mySpace.downSpace = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->bottomBoundary + relativeLocation;
	mySpace.leftSpace = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->leftBoundary + relativeLocation;
	mySpace.rightSpace = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->rightBoundary + relativeLocation;
	mySpace.upSpace = Prefabs[prefabNo]->GetDefaultObject<APrefab>()->topBoundary + relativeLocation;
	return mySpace;
}

