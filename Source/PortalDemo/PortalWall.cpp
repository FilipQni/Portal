// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalWall.h"

// Sets default values
APortalWall::APortalWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APortalWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortalWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

