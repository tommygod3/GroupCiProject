#pragma once

#include "CoreMinimal.h"
#include "CiProjectStructs.generated.h"

USTRUCT()
struct FworldSpace
{
	GENERATED_BODY()

	UPROPERTY()
	FVector leftSpace;
	UPROPERTY()
	FVector upSpace;
	UPROPERTY()
	FVector rightSpace;
	UPROPERTY()
	FVector downSpace;
};
