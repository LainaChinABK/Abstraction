// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "SlidingDoor.generated.h"

class USlidingDoorComponent;

UCLASS()
class ABSTRACTION_API ASlidingDoor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ASlidingDoor();

protected:
	UPROPERTY(EditAnywhere, NoClear)
	USlidingDoorComponent* SlidingDoorComponent;
};
