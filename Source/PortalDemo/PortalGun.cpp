// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalGun.h"
#include "PortalManager.h"

// Sets default values
APortalGun::APortalGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void APortalGun::BeginPlay()
{
	Super::BeginPlay();

	PortalManager = GetWorld()->SpawnActor<APortalManager>(PortalManagerClass);
}

// Called every frame
void APortalGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APortalGun::CreatePortalEnter()
{
	FHitResult Hit;
	Shot(Hit);
	if(Shot(Hit) && Hit.GetActor() != nullptr)
	{
		PortalManager->CreatePortalEnter(Hit);
		UE_LOG(LogTemp, Warning, TEXT("Stworzono Enter Portal"));
	}
}

void APortalGun::CreatePortalExit()
{
	FHitResult Hit;
	if(Shot(Hit) && Hit.GetActor() != nullptr)
	{
		PortalManager->CreatePortalExit(Hit);
		UE_LOG(LogTemp, Warning, TEXT("Stworzono Enter Portal"));
	}
}

bool APortalGun::Shot(FHitResult &Hit)
{
	FVector ShotDirection;
	bool bSuccess = PortalGunTrace(Hit, ShotDirection);
	return bSuccess;
	//TODO: Animacja i dźwięk strzału
	if(bSuccess)
	{
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
	}
}

bool APortalGun::PortalGunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController *OwnerController = GetOwnerController();
	if(OwnerController == nullptr)
		return false;
	
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	
	FVector End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* APortalGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr)
		return nullptr;
	return OwnerPawn->GetController();
}


