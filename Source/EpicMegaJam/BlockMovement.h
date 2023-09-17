// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "BlockMovement.generated.h"

// Handles entire Block behavior
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EPICMEGAJAM_API UBlockMovement : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBlockMovement();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Interaction State Variables
	bool IsPlaced;

private:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupPlayerInputComponent();

	// Draws debug elements
	void DebugDraw();

	// Movement Methods
	// {TargetDirection}: 0 - Left 1 - Right
	void SetNewTarget(float TargetRange, bool IsRight);
	void MoveToTarget(float DeltaTime);

	// Interaction State Methods
	void PlaceBlock(); // Called when Player interacts with block ("Spacebar" press) 

	UStaticMeshComponent* BlockMesh;

	// Movement Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float LeftRange = -400.f; // Need to match bounds from Generated Tower
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RightRange = 400.f; // Need to match bounds from Generated Tower
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 500.f;

	bool IsGoingRight; // 0 - Left 1 - Right
	FVector CurrentTarget;
	FVector Direction;
	float TotalDistance;
	float CurrentDistance;
	FVector StartLocation;
};
