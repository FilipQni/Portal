// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxSpawningTube.h"

#include "MyBox.h"

// Sets default values
ABoxSpawningTube::ABoxSpawningTube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(Root);

	WallOneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First Wall Mesh"));
	WallOneMesh->SetupAttachment(BaseMesh);

	WallTwoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second Wall Mesh"));
	WallTwoMesh->SetupAttachment(BaseMesh);

	WallThreeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Third Wall Mesh"));
	WallThreeMesh->SetupAttachment(BaseMesh);

	WallFourMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fourth Wall Mesh"));
	WallFourMesh->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void ABoxSpawningTube::BeginPlay()
{
	Super::BeginPlay();

	BoxSpawnRotation = this->GetActorRotation();
	BoxSpawnLocation = this->GetActorLocation();
	BoxSpawnLocation.Z -= 100;
}

// Called every frame
void ABoxSpawningTube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoxSpawningTube::SpawnBox()
{
	if (Box != nullptr)
		Box->Destroy();

	Box = GetWorld()->SpawnActor<AMyBox>(BoxClass, BoxSpawnLocation, BoxSpawnRotation);
}

void ABoxSpawningTube::ReactToInteraction()
{
	this->SpawnBox();
	UE_LOG(LogTemp, Warning, TEXT("Box has been spawned"));
}
