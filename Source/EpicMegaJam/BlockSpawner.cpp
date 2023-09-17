// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockSpawner.h"

UBlockSpawner::UBlockSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UBlockSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnBlock(); // TODO: delete, for debug
}

void UBlockSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// TODO: Check if the current ActiveBlock is placed and if so call SpawnBlock() again
}

void UBlockSpawner::SpawnBlock()
{
	if (ActorToSpawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UBlockSpawner: ActorToSpawn variable is null."));
		return;
	}

	ActiveBlock = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnTransform);
}



