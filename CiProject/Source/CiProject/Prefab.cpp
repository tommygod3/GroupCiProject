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