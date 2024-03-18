// Fill out your copyright notice in the Description page of Project Settings.


#include "SignalDot.h"

// Sets default values
ASignalDot::ASignalDot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dot Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ASignalDot::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASignalDot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASignalDot::TurnOn() const
{
	Mesh->SetMaterial(0, DotOnMaterial);
}

void ASignalDot::TurnOff() const
{
	Mesh->SetMaterial(0, DotOffMaterial);
}

int ASignalDot::GetId() const
{
	return Id;
}

