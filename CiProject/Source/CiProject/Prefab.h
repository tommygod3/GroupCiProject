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
	FVector leftConnector = FVector(-100.0f, 0.0f, 10.0f);
	
	UFUNCTION(BlueprintCallable)
	FVector getLeftConnector();

	UPROPERTY(EditAnywhere)
	FVector rightConnector = FVector(100.0f, 0.0f, 10.0f);

	UFUNCTION(BlueprintCallable)
	FVector getRightConnector();

	UFUNCTION(BlueprintImplementableEvent, Category = "Set")
	void CalledFromCpp();
};
