// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	StartRotation = GetOwner()->GetActorRotation();
	FrontTriggerFinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
	BackTriggerFinalRotation = GetOwner()->GetActorRotation() + DesiredRotation.Add(0.0f, 180.0f, 0.0f);
	CurrentRotationTime = 0.0f;
	
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentRotationTime >= TimeToRotate)
	{
		CurrentRotationTime = TimeToRotate - DeltaTime;
	}
	if (CurrentRotationTime < 0.0f)
	{
		CurrentRotationTime = 0.0f;
	}

	if (CurrentRotationTime < TimeToRotate)
	{
		if (FrontTriggerBox || BackTriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			FRotator FinalRotation = FRotator::ZeroRotator;

			if (PlayerPawn && FrontTriggerBox && FrontTriggerBox->IsOverlappingActor(PlayerPawn))
			{
				FinalRotation = FrontTriggerFinalRotation;
				lastTrigger = 0;
				rotating = true;
			}

			else if (PlayerPawn && BackTriggerBox && BackTriggerBox->IsOverlappingActor(PlayerPawn))
			{
				FinalRotation = BackTriggerFinalRotation;
				lastTrigger = 1;
				rotating = true;
			}

			// either trigger
			if (rotating)
			{
				CurrentRotationTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);

				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
			}

			else
			{
				CurrentRotationTime -= DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				if (lastTrigger == 0)
				{
					const FRotator CurrentRotation = FMath::Lerp(StartRotation, FrontTriggerFinalRotation, RotationAlpha);
					GetOwner()->SetActorRotation(CurrentRotation);
				}
				else
				{
					const FRotator CurrentRotation = FMath::Lerp(StartRotation, BackTriggerFinalRotation, RotationAlpha);
					GetOwner()->SetActorRotation(CurrentRotation);
				}
			}
		}
	}

	// this line could probably go somewhere else
	rotating = false;
}

