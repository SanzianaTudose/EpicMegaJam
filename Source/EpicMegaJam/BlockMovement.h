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

private:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupPlayerInputComponent();

	// Movement Methods
	// {TargetDirection}: 0 - Left 1 - Right
	void SetNewTarget(float TargetRange, bool isRight);
	void MoveToTarget(float DeltaTime);
	void StopMovement(); // Called when Player interacts with block ("Spacebar" press) 

	// Draws debug elements
	void DebugDraw();

	// Movement Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float LeftRange = -350.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RightRange = 350.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 500.f;

	bool isGoingRight; // 0 - Left 1 - Right
	FVector CurrentTarget;
	FVector Direction;
	float TotalDistance;
	float CurrentDistance;
	FVector StartLocation;

	bool isMoving;
};
