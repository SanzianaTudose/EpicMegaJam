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


float UScoringComponent::ScoreBlocks(TArray<int32> exampleBlocks, TArray<int32> userBlocks)
{
	float error = 0;
	int examplePrevPos = -400, userPrevPos = 1100;

	for (int32 i = 0; i != userBlocks.Num(); ++i)
	{
		//get difference to previous position
		int exampleDelta = exampleBlocks[i] - examplePrevPos;
		int userDelta = userBlocks[i] - userPrevPos;

		//update previous position
		examplePrevPos = exampleBlocks[i];
		userPrevPos = userBlocks[i];

		//calculate difference between towers
		float diff = exampleDelta - userDelta;
		diff /= PenaltyPerUnit;
		//calculate absolute error

		if(diff < 0)
		{
			diff = -diff;
		}
		UE_LOG(LogTemp, Warning, TEXT("%f"), diff);

		error += diff;
	}
	error /= userBlocks.Num();//calculate average error
	error = 10 - error;//calculate score out of 10
	if(error < 0)
	{
		error = 0;
	}

	return error;
	// return exampleBlocks[0] + 400;
	// return userBlocks[0] - 1100;

}

