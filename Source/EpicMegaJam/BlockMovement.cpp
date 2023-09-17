// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockMovement.h"
#include "DrawDebugHelpers.h"

UBlockMovement::UBlockMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UBlockMovement::BeginPlay()
{
	Super::BeginPlay();

	// DEBUG ONLY! 
	DebugDraw();

	SetupPlayerInputComponent();

	// Sets the first target to left
	SetNewTarget(LeftTarget, 0);
	isMoving = true;
}

void UBlockMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isMoving)
		MoveToTarget(DeltaTime);

	// Check if CurrentTarget is reached and switch targets
	if (CurrentDistance >= TotalDistance)
	{
		if (isGoingRight)
			SetNewTarget(LeftTarget, 0);
		else
			SetNewTarget(RightTarget, 1);
	}
}

void UBlockMovement::SetupPlayerInputComponent()
{
	UInputComponent* InputComponent = GetWorld()->GetFirstPlayerController()->FindComponentByClass<UInputComponent>();

	if (InputComponent != nullptr)
		InputComponent->BindAction("Stop Block", IE_Pressed, this, &UBlockMovement::StopMovement);
}

void UBlockMovement::SetNewTarget(FVector TargetLocation, bool isRight)
{
	CurrentTarget = TargetLocation;
	isGoingRight = isRight;

	StartLocation = GetOwner()->GetActorLocation();
	Direction = CurrentTarget - StartLocation;
	TotalDistance = Direction.Size();

	// Normalize Direction
	Direction = Direction.GetSafeNormal();
	CurrentDistance = 0.0f;
}

void UBlockMovement::MoveToTarget(float DeltaTime)
{
	if (CurrentDistance < TotalDistance)
	{
		FVector Location = GetOwner()->GetActorLocation();

		Location += Direction * MoveSpeed * DeltaTime;

		GetOwner()->SetActorLocation(Location);

		CurrentDistance = (Location - StartLocation).Size();
	}
}

void UBlockMovement::StopMovement()
{
	isMoving = !isMoving;
}

void UBlockMovement::DebugDraw()
{
	DrawDebugSphere(GetWorld(), LeftTarget, 10, 50, FColor::Green, true);
	DrawDebugSphere(GetWorld(), RightTarget, 10, 50, FColor::Green, true);
}