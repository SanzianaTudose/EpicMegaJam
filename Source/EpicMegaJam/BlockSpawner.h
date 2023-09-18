// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlockMovement.h"
#include "BlockSpawner.generated.h"

// Handles spawning Blocks 
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EPICMEGAJAM_API UBlockSpawner : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlockSpawner();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<int32> PlayerBlocksPositions; // After all Blocks are spawned, it holds their final Y values (for scoring)

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Is called with a delay in order to wait for the Planned Tower Generation 
	void StartSpawningTask();
	void SpawnBlock();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning Properties", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning Properties", meta = (AllowPrivateAccess = "true"));
	FTransform SpawnTransform = FTransform(FVector(0.f, 0.f, 800.f));
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning Properties", meta = (AllowPrivateAccess = "true"));
	float BlockSpawnDelay = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning Properties", meta = (AllowPrivateAccess = "true"));
	float InitialSpawnDelay = 7.f; // Needs to be adjusted depending on how long Planned Tower Generation takes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning Properties", meta = (AllowPrivateAccess = "true"));
	int PlayerTowerHeight = 6; // Needs to be adjusted to match Planned Tower 

	int SpawnedBlockCount;
	bool SpawningStarted;
	bool SpawnQueued;
	AActor* ActiveBlock;
	UBlockMovement* BlockMovementComp;
};
