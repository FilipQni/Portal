// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActor.h"

// Sets default values
AInteractiveActor::AInteractiveActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bActive = false;
}

// Called when the game starts or when spawned
void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AInteractiveActor::IsActive() const
{
	return this->bActive;
}

void AInteractiveActor::ReactToInteraction()
{
	UE_LOG(LogTemp, Warning, TEXT("ReactToInteraction works from the AInteractiveActor"));
}

