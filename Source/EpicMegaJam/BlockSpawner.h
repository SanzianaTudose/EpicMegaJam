// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlockSpawner.generated.h"

// Handles spawning Blocks 
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EPICMEGAJAM_API UBlockSpawner : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBlockSpawner();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupPlayerInputComponent();

	void OnBlockSpawnPress();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> ActorToSpawn;

};
