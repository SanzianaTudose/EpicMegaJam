// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoringComponent.h"

// Sets default values for this component's properties
UScoringComponent::UScoringComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScoringComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UScoringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


int UScoringComponent::ScoreBlocks(TArray<int32> exampleBlocks, TArray<int32> userBlocks)
{
	int error = 0;

	for (int32 i = 0; i != exampleBlocks.Num(); ++i)
	{
		int diff = exampleBlocks[i];// - userBlocks[i];
		diff *= diff;
		error += diff;
	}

	return error;
}

