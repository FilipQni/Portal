// Fill out your copyright notice in the Description page of Project Settings.


#include "SignalDotManager.h"

#include "CheckboxPlate.h"
#include "EngineUtils.h"
#include "SignalDot.h"

// Sets default values
ASignalDotManager::ASignalDotManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASignalDotManager::BeginPlay()
{
	Super::BeginPlay();

	bActive = false;

	TArray<ASignalDot*> DotActors;
	for (TActorIterator<ASignalDot> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Add the actor to the array
		if (ActorItr->GetId() == Id)
			DotsArray.Add(*ActorItr);
	}
	UE_LOG(LogTemp, Warning, TEXT("DotManager has: %i dots"), DotsArray.Num());
}

// Called every frame
void ASignalDotManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASignalDotManager::Interact()
{
	bActive = !bActive;

	if (bActive)
	{
		for (ASignalDot* Dot : DotsArray)
		{
			Dot->TurnOn();
			CheckboxPlate->TurnOn();
		}
	}
	else
	{
		for (ASignalDot* Dot : DotsArray)
		{
			Dot->TurnOff();
			CheckboxPlate->TurnOff();
		}
	}
}
