// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USlidingDoorComponent::USlidingDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlidingDoorComponent::BeginPlay()
{
	Super::BeginPlay();
	StartVector = GetOwner()->GetActorLocation();
	FinalVector = GetOwner()->GetActorLocation() + DesiredPath;
	CurrentTime = 0.0f;
	
}


// Called every frame
void USlidingDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentTime < TravelTime)
	{
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
			{
				CurrentTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentTime / TravelTime, 0.0f, 1.0f);
				const float Alpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);

				const FVector CurrentVector = FMath::Lerp(StartVector, FinalVector, Alpha);
				GetOwner()->SetActorLocation(CurrentVector);
			}
		}
	}
}

