// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS()
class CIPROJECT_API ALevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

	UPROPERTY (EditAnywhere)
	TSubclassOf<class AStaticMeshActor> PF1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AStaticMeshActor> PF2;

	UPROPERTY(EditAnywhere)
	int32 NumberOfPrefabs;

	UPROPERTY(EditAnywhere)
	int32 NumberOfRooms;

	UFUNCTION(BlueprintCallable)
	void Spawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

	
	
};
