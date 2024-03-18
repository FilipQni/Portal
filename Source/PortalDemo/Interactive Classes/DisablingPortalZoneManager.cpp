// Fill out your copyright notice in the Description page of Project Settings.


#include "DisablingPortalZoneManager.h"
#include "DisablingPortalZone.h"

// Sets default values
ADisablingPortalZoneManager::ADisablingPortalZoneManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADisablingPortalZoneManager::BeginPlay()
{
	Super::BeginPlay();

	DisPortalZonePosition = DisablingPortalZone->GetActorLocation();
	DisPortalZoneScale = DisablingPortalZone->GetActorScale3D();
	DisPortalZoneRotation = DisablingPortalZone->GetActorRotation();

	if (!bActive)
		DisablingPortalZone->Destroy();
}

// Called every frame
void ADisablingPortalZoneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADisablingPortalZoneManager::ReactToInteraction()
{
	bActive = !bActive;
	if (bActive)
		CreateDisablingPortalZone();
	else DisablingPortalZone->Destroy();
}

void ADisablingPortalZoneManager::CreateDisablingPortalZone()
{
	DisablingPortalZone = GetWorld()->SpawnActor<ADisablingPortalZone>(DisablingPortalZoneClass, DisPortalZonePosition,
	                                                                   DisPortalZoneRotation);
	DisablingPortalZone->SetActorScale3D(DisPortalZoneScale);
}
