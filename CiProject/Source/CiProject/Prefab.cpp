// Fill out your copyright notice in the Description page of Project Settings.

#include "Prefab.h"


// Sets default values
APrefab::APrefab()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APrefab::BeginPlay()
{
	Super::BeginPlay();
}

void APrefab::OnConstruction(const FTransform& transform)
{
	SetBoundaries();
}

// Called every frame
void APrefab::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector APrefab::getLeftBoundary()
{
	return leftBoundary;
}

FVector APrefab::getRightBoundary()
{
	return rightBoundary;
}

FVector APrefab::getTopBoundary()
{
	return topBoundary;
}

FVector APrefab::getBottomBoundary()
{
	return bottomBoundary;
}

FTransform APrefab::getPotentialGem1()
{
	return potentialGem1;
}

FTransform APrefab::getPotentialGem2()
{
	return potentialGem2;
}

FTransform APrefab::getPotentialSpike1()
{
	return potentialSpike1;
}

FTransform APrefab::getPotentialSpike2()
{
	return potentialSpike2;
}

unsigned int APrefab::noOfConnectors()
{
	unsigned int count = 0;
	if (rightBoundaryIsConnector)
	{
		count++;
	}
	if (leftBoundaryIsConnector)
	{
		count++;
	}
	if (topBoundaryIsConnector)
	{
		count++;
	}
	if (bottomBoundaryIsConnector)
	{
		count++;
	}
	return count;
}