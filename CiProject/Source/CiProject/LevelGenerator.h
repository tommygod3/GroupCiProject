// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Prefab.h"
#include "CiProjectStructs.h"

#include "LevelGenerator.generated.h"



UCLASS()
class CIPROJECT_API ALevelGenerator : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class APrefab>> Prefabs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blueprints)
	TSubclassOf<class AActor> gemBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blueprints)
	TSubclassOf<class AActor> spikeBP;

	UPROPERTY(EditAnywhere)
	uint32 NumberOfRooms;

	UPROPERTY(EditAnywhere)
	uint32 NumberOfGems;

	UPROPERTY(EditAnywhere)
	uint32 NumberOfSpikes;

	UPROPERTY(EditAnywhere)
	int32 Seed;

	UFUNCTION(BlueprintCallable)
	void Spawn();

	void SpawnPrefab(FVector locationWorld, FVector locationRelative, char connector);
	void worldSpawnPrefab(unsigned int prefabNo, FVector location, UWorld* world);
	void worldSpawnGems(unsigned int prefabNo, unsigned int numOfGems, FVector location, UWorld* world);
	void worldSpawnSpikes(unsigned int prefabNo, unsigned int numOfSpikes, FVector location, UWorld* world);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	unsigned int noOfConnectors(unsigned int prefabNo);
	bool validatePrefab(unsigned int prefabNo);
	FworldSpace getSpace(unsigned int prefabNo, FVector relativeLocation);

	unsigned int spawned = 0;
	unsigned int toBeSpawned = 0;

	TArray<FworldSpace> spaces;

};

