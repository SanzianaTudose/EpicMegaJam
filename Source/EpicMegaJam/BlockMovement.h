// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlockMovement.generated.h"


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

	void SetNewTarget(AActor* Target);
	void MoveToTarget(float DeltaTime);

	// Movement Variables
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	AActor* LeftTarget;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	AActor* RightTarget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 100.f;

	AActor* CurrentTarget;
	FVector Direction;
	float TotalDistance;
	float CurrentDistance;
	FVector StartLocation;
};
