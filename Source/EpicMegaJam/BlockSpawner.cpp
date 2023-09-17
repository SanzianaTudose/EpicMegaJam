// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockSpawner.h"
#include "Engine/World.h"

UBlockSpawner::UBlockSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UBlockSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnBlock();
}

void UBlockSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (BlockMovementComp->IsPlaced && !SpawnQueued)
	{
		SpawnQueued = true;

		// Spawn next block with a delay
		FTimerHandle SpawnDelayTimer;
		GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimer, this, &UBlockSpawner::SpawnBlock, SpawnDelay, false);
	}
}

void UBlockSpawner::SpawnBlock()
{
	if (ActorToSpawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UBlockSpawner: ActorToSpawn variable is null."));
		return;
	}

	SpawnQueued = false;

	ActiveBlock = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnTransform);
	BlockMovementComp = ActiveBlock->FindComponentByClass<UBlockMovement>();

	if (BlockMovementComp == nullptr)
		UE_LOG(LogTemp, Error, TEXT("UBlockSpawner: ActiveBlock is null."));
	if (ActiveBlock == nullptr)
		UE_LOG(LogTemp, Error, TEXT("UBlockSpawner: UBlockMovement component could not be found on ActiveBlock."));
}



