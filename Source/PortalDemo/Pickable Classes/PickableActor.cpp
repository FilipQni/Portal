// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor.h"


// Sets default values
APickableActor::APickableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);

	bGravity = true;
	bHeld = false;
}

// Called when the game starts or when spawned
void APickableActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickableActor::Interact()
{
	bGravity = false;
	bHeld = true;
	MeshComponent->SetSimulatePhysics(bGravity);
	this->SetActorEnableCollision(false);
}

void APickableActor::Drop()
{
	bGravity = true;
	bHeld = false;
	this->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	this->SetActorEnableCollision(true);
	MeshComponent->SetSimulatePhysics(bGravity);
}

void APickableActor::Throw(FVector CameraForwardVector)
{
	bGravity = true;
	bHeld = false;
	const double NewSpeed = 1000;
	FVector NewVelocity = CameraForwardVector * NewSpeed;

	this->SetActorEnableCollision(true);
	MeshComponent->SetSimulatePhysics(bGravity);

	Cast<UPrimitiveComponent>(RootComponent)->SetPhysicsLinearVelocity(NewVelocity);
}
