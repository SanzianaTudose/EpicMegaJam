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

	SpawnedBlockCount = 0;

	// Set a timer to delay the spawning of the first Block
	SpawningStarted = false;
	FTimerHandle InitialSpawnDelayTimer;
	GetWorld()->GetTimerManager().SetTimer(InitialSpawnDelayTimer, this, &UBlockSpawner::StartSpawningTask, InitialSpawnDelay, false);
}

void UBlockSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Stay idle if spawning delay is not over yet
	if (!SpawningStarted) return;

	if (BlockMovementComp->IsPlaced && !SpawnQueued)
	{
		SpawnQueued = true;

		// Spawn next block with a delay
		FTimerHandle BlockSpawnDelayTimer;
		GetWorld()->GetTimerManager().SetTimer(BlockSpawnDelayTimer, this, &UBlockSpawner::SpawnBlock, BlockSpawnDelay, false);
	}
}

void UBlockSpawner::StartSpawningTask()
{
	SpawnBlock();
	SpawningStarted = true;
}

void UBlockSpawner::SpawnBlock()
{
	if (ActorToSpawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UBlockSpawner: ActorToSpawn variable is null."));
		return;
	}

	if (SpawnedBlockCount == PlayerTowerHeight)
		return; // TODO: Call scoring here (?)

	SpawnQueued = false;

	ActiveBlock = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnTransform);
	BlockMovementComp = ActiveBlock->FindComponentByClass<UBlockMovement>();
	SpawnedBlockCount++;

	if (BlockMovementComp == nullptr)
		UE_LOG(LogTemp, Error, TEXT("UBlockSpawner: ActiveBlock is null."));
	if (ActiveBlock == nullptr)
		UE_LOG(LogTemp, Error, TEXT("UBlockSpawner: UBlockMovement component could not be found on ActiveBlock."));
}



