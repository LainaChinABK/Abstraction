// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalDoor.h"
#include "GoalComponent.h"

AGoalDoor::AGoalDoor()
{
	GoalComponent = CreateDefaultSubobject<UGoalComponent>(TEXT("GoalComponent"));
}