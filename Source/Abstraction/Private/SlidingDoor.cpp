// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoor.h"
#include "SlidingDoorComponent.h"

ASlidingDoor::ASlidingDoor()
{
	SlidingDoorComponent = CreateDefaultSubobject<USlidingDoorComponent>(TEXT("SlidingDoorComponent"));
}
