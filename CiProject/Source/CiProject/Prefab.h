// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Prefab.generated.h"

UCLASS()
class CIPROJECT_API APrefab : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APrefab();

	virtual void OnConstruction(const FTransform& transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FVector leftBoundary;
	
	UFUNCTION(BlueprintCallable)
	FVector getLeftBoundary();

	UPROPERTY(EditAnywhere)
	bool leftBoundaryIsConnector;

	UPROPERTY(EditAnywhere)
	FVector rightBoundary;

	UFUNCTION(BlueprintCallable)
	FVector getRightBoundary();

	UPROPERTY(EditAnywhere)
	bool rightBoundaryIsConnector;

	UPROPERTY(EditAnywhere)
	FVector topBoundary;

	UFUNCTION(BlueprintCallable)
	FVector getTopBoundary();

	UPROPERTY(EditAnywhere)
	bool topBoundaryIsConnector;

	UPROPERTY(EditAnywhere)
	FVector bottomBoundary;

	UFUNCTION(BlueprintCallable)
	FVector getBottomBoundary();

	UPROPERTY(EditAnywhere)
	bool bottomBoundaryIsConnector;

	UPROPERTY(EditAnywhere)
	FTransform potentialGem1;

	UFUNCTION(BlueprintCallable)
	FTransform getPotentialGem1();

	UPROPERTY(EditAnywhere)
	FTransform potentialGem2;

	UFUNCTION(BlueprintCallable)
	FTransform getPotentialGem2();

	UPROPERTY(EditAnywhere)
	FTransform potentialSpike1;

	UFUNCTION(BlueprintCallable)
	FTransform getPotentialSpike1();

	UPROPERTY(EditAnywhere)
	FTransform potentialSpike2;

	UFUNCTION(BlueprintCallable)
	FTransform getPotentialSpike2();

	UFUNCTION(BlueprintImplementableEvent, Category = "Set")
	void SetBoundaries();

	unsigned int noOfConnectors();


};
