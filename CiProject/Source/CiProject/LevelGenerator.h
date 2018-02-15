// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Prefab.h"

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

	UPROPERTY(EditAnywhere)
	int32 NumberOfRooms;

	UPROPERTY(EditAnywhere)
	int32 Seed;

	UFUNCTION(BlueprintCallable)
	void Spawn();

	void SpawnPrefab(FVector locationWorld, FVector locationRelative, char connector, int& spawned);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
