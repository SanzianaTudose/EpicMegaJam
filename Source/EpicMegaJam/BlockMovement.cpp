// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockMovement.h"

UBlockMovement::UBlockMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UBlockMovement::BeginPlay()
{
	Super::BeginPlay();

	if (LeftTarget == nullptr || RightTarget == nullptr)
		UE_LOG(LogTemp, Error, TEXT("UBlockMovement target variables are null"));

	// Sets the first target to left
	SetNewTarget(LeftTarget, 0);
}

void UBlockMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveToTarget(DeltaTime);

	if (CurrentDistance >= TotalDistance)
	{
		if (CurrentTargetDirection)
			SetNewTarget(LeftTarget, 0);
		else
			SetNewTarget(RightTarget, 1);
	}
}

void UBlockMovement::SetNewTarget(AActor* Target, bool TargetDirection)
{
	CurrentTarget = Target;
	CurrentTargetDirection = TargetDirection;

	StartLocation = GetOwner()->GetActorLocation();
	Direction = Target->GetActorLocation() - StartLocation;
	TotalDistance = Direction.Size();

	// Normalize Direction
	Direction = Direction.GetSafeNormal();
	CurrentDistance = 0.0f;
}

void UBlockMovement::MoveToTarget(float DeltaTime)
{
	if (CurrentTarget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UBlockMovement: CurrentTarget variable is null."));
		return;
	}

	if (CurrentDistance < TotalDistance)
	{
		FVector Location = GetOwner()->GetActorLocation();

		Location += Direction * MoveSpeed * DeltaTime;

		GetOwner()->SetActorLocation(Location);

		CurrentDistance = (Location - StartLocation).Size();
	}
}