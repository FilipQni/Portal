// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckboxPlate.h"

// Sets default values
ACheckboxPlate::ACheckboxPlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dot Mesh"));
	Mesh->SetupAttachment(Root);
}


// Called when the game starts or when spawned
void ACheckboxPlate::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACheckboxPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACheckboxPlate::TurnOn() const
{
	Mesh->SetMaterial(0, CheckboxOnMaterial);
}

void ACheckboxPlate::TurnOff() const
{
	Mesh->SetMaterial(0, CheckboxOffMaterial);
}