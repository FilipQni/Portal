// Fill out your copyright notice in the Description page of Project Settings.


#include "MyButton.h"

AMyButton::AMyButton()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	MeshBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	MeshBase->SetupAttachment(Root);

	MeshStand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stand Mesh"));
	MeshStand->SetupAttachment(Root);

	MeshButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Mesh"));
	MeshButton->SetupAttachment(Root);
}

void AMyButton::ReactToInteraction()
{
	ObjectToInteract->ReactToInteraction();
}
