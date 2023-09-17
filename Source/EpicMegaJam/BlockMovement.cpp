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

	SetupPlayerInputComponent();

	IsPlaced = false;
	StartLocation = GetOwner()->GetActorLocation();
	BlockMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	if (BlockMesh == nullptr)
		UE_LOG(LogTemp, Error, TEXT("UBlockMovement: Static Mesh could not be found on Block."));

	// Sets the first target to left
	SetNewTarget(LeftRange, 0);

	DebugDraw(); // DEBUG ONLY! 
}

void UBlockMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Only move Block if it has not been placed yet
	if (!IsPlaced)
	{
		MoveToTarget(DeltaTime);

		// Check if CurrentTarget is reached and switch targets
		if (CurrentDistance >= TotalDistance)
		{
			if (IsGoingRight)
				SetNewTarget(LeftRange, 0);
			else
				SetNewTarget(RightRange, 1);
		}
	}
}

void UBlockMovement::SetupPlayerInputComponent()
{
	UInputComponent* InputComponent = GetWorld()->GetFirstPlayerController()->FindComponentByClass<UInputComponent>();

	if (InputComponent != nullptr)
		InputComponent->BindAction("Block Place", IE_Pressed, this, &UBlockMovement::PlaceBlock);
}

void UBlockMovement::SetNewTarget(float TargetRange, bool IsRight)
{
	CurrentTarget = FVector(StartLocation.X, StartLocation.Y + TargetRange, StartLocation.Z);
	IsGoingRight = IsRight;

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

void UBlockMovement::PlaceBlock()
{
	if (IsPlaced) return;

	IsPlaced = !IsPlaced;
	// Lock Block's X and Y positions
	BlockMesh->GetBodyInstance()->bLockXTranslation = true;
	BlockMesh->GetBodyInstance()->bLockYTranslation = true;

	// Enable gravity so that block falls
	BlockMesh->SetEnableGravity(true);
}

void UBlockMovement::DebugDraw()
{
	DrawDebugSphere(GetWorld(), FVector(StartLocation.X, StartLocation.Y + LeftRange, StartLocation.Z), 10, 50, FColor::Green, true);
	DrawDebugSphere(GetWorld(), FVector(StartLocation.X, StartLocation.Y + RightRange, StartLocation.Z), 10, 50, FColor::Green, true);
}