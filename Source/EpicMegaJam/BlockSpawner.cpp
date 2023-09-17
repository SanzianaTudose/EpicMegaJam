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

	SetupPlayerInputComponent();
}

void UBlockSpawner::SetupPlayerInputComponent()
{
	UInputComponent* InputComponent = GetWorld()->GetFirstPlayerController()->FindComponentByClass<UInputComponent>();

	if (InputComponent != nullptr)
		InputComponent->BindAction("Block Spawn", IE_Pressed, this, &UBlockSpawner::OnBlockSpawnPress);
}

void UBlockSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBlockSpawner::OnBlockSpawnPress()
{
	if (ActorToSpawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UBlockSpawner: ActorToSpawn variable is null."));
		return;
	}
	GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetOwner()->GetActorTransform());
}



