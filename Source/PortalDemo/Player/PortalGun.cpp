// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalGun.h"
#include "PortalDemo/Portals/Portal Walls/PortalWallInterface.h"
#include "PortalDemo/Portals/PortalManager.h"
#include "Kismet/GameplayStatics.h"

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

	PortalManager = Cast<APortalManager>(UGameplayStatics::GetActorOfClass(GetWorld(), APortalManager::StaticClass()));
}

// Called every frame
void APortalGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APortalGun::CreatePortalEnter()
{
	FHitResult Hit;
	if (Shot(Hit, ECC_GameTraceChannel1) && Hit.GetActor() != nullptr && Hit.GetActor()->Implements<
		UPortalWallInterface>())
	{
		if (FixPortalPosition(Hit, ECC_GameTraceChannel1))
			PortalManager->CreatePortalEnter(Hit);
	}
}

void APortalGun::CreatePortalExit()
{
	FHitResult Hit;
	if (Shot(Hit, ECC_GameTraceChannel2) && Hit.GetActor() != nullptr && Hit.GetActor()->Implements<
		UPortalWallInterface>())
	{
		if (FixPortalPosition(Hit, ECC_GameTraceChannel2))

			PortalManager->CreatePortalExit(Hit);
	}
}

bool APortalGun::Shot(FHitResult& Hit, ECollisionChannel CollisionChannel)
{
	FVector ShotDirection;
	bool GunTraceResult = PortalGunTrace(Hit, ShotDirection, CollisionChannel);

	return GunTraceResult;
	//TODO: Animacja i dźwięk strzału
	if (GunTraceResult)
	{
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
	}
}


bool APortalGun::PortalGunTrace(FHitResult& Hit, FVector& ShotDirection, ECollisionChannel CollisionChannel) const
{
	const AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
		return false;

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	const FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, CollisionChannel, Params);
}

bool APortalGun::FixPortalPosition(FHitResult& PortalHit, ECollisionChannel CollisionChannel)
{
	FVector ArrayOfVectors[8];
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	FVector Location = PortalHit.Location + PortalHit.Normal * 100;

	FVector RightOffset = PortalHit.Normal.Rotation().RotateVector(FVector::LeftVector);
	ArrayOfVectors[0] = Location + RightOffset * 85.0; // Right Position
	ArrayOfVectors[1] = Location + RightOffset * -85.0; // Left Position

	FVector AboveOffset = PortalHit.Normal.Rotation().RotateVector(FVector::UpVector);
	ArrayOfVectors[2] = Location + AboveOffset * 140.0; // Above Position
	ArrayOfVectors[3] = Location + AboveOffset * -140.0; // Below Position

	ArrayOfVectors[4] = Location + RightOffset * 55.0 + AboveOffset * 105; // Right Above Position
	ArrayOfVectors[5] = Location + RightOffset * 55.0 + AboveOffset * -105; // Right Below Position
	ArrayOfVectors[6] = Location + RightOffset * -55.0 + AboveOffset * 105; // Left Above Position
	ArrayOfVectors[7] = Location + RightOffset * -55.0 + AboveOffset * -105; // Left Below Position

	FHitResult FirstOffsetHit;
	FHitResult SecondOffsetHit;

	DrawDebugLine(GetWorld(), ArrayOfVectors[0], (ArrayOfVectors[0] - PortalHit.Normal * 200), FColor::Red, false, 8, 0,
	              1);
	DrawDebugLine(GetWorld(), ArrayOfVectors[1], (ArrayOfVectors[1] - PortalHit.Normal * 200), FColor::Red, false, 8, 0,
	              1);
	DrawDebugLine(GetWorld(), ArrayOfVectors[2], (ArrayOfVectors[2] - PortalHit.Normal * 200), FColor::Red, false, 8, 0,
	              1);
	DrawDebugLine(GetWorld(), ArrayOfVectors[3], (ArrayOfVectors[3] - PortalHit.Normal * 200), FColor::Red, false, 8, 0,
	              1);

	//Left and right positions
	GetWorld()->LineTraceSingleByChannel(FirstOffsetHit, ArrayOfVectors[0],
	                                     (ArrayOfVectors[0] - PortalHit.Normal * 200),
	                                     CollisionChannel,
	                                     Params);
	GetWorld()->LineTraceSingleByChannel(SecondOffsetHit, ArrayOfVectors[1],
	                                     (ArrayOfVectors[1] - PortalHit.Normal * 200),
	                                     CollisionChannel,
	                                     Params);

	ShiftPortalPositionIfNeeded(FirstOffsetHit, SecondOffsetHit, PortalHit, ArrayOfVectors[0], ArrayOfVectors[1],
	                            RightOffset, CollisionChannel);

	//Upper and lower positions
	GetWorld()->LineTraceSingleByChannel(FirstOffsetHit, ArrayOfVectors[2],
	                                     (ArrayOfVectors[2] - PortalHit.Normal * 200),
	                                     CollisionChannel,
	                                     Params);
	GetWorld()->LineTraceSingleByChannel(SecondOffsetHit, ArrayOfVectors[3],
	                                     (ArrayOfVectors[3] - PortalHit.Normal * 200),
	                                     CollisionChannel,
	                                     Params);

	ShiftPortalPositionIfNeeded(FirstOffsetHit, SecondOffsetHit, PortalHit, ArrayOfVectors[2], ArrayOfVectors[3],
	                            AboveOffset, CollisionChannel);

	return IsPortalPositionAvailable(PortalHit, Params, ArrayOfVectors, CollisionChannel);
}

bool APortalGun::IsPortalPositionAvailable(FHitResult& PortalHit, FCollisionQueryParams& Params,
                                           FVector ArrayOfVectors[8], ECollisionChannel CollisionChannel)
{
	FHitResult Hit;

	for (int i = 0; i < 8; i++)
	{
		GetWorld()->LineTraceSingleByChannel(Hit, ArrayOfVectors[i], (ArrayOfVectors[i] - PortalHit.Normal * 200),
		                                     CollisionChannel,
		                                     Params);
		if (Hit.GetActor() != nullptr && !Hit.GetActor()->Implements<UPortalWallInterface>())
			return false;
	}


	return true;
}

void APortalGun::ShiftPortalPosition(FHitResult& HitToShift, FVector& Location,
                                     const FVector& DirectionVector, ECollisionChannel CollisionChannel) const
{
	bool IsFixed = false;
	int Counter = 0;
	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	do
	{
		Counter++;
		Location = Location + DirectionVector * 20.0;
		GetWorld()->LineTraceSingleByChannel(Hit, Location, (Location - HitToShift.Normal * 200),
		                                     CollisionChannel,
		                                     Params);

		if (Hit.GetActor() != nullptr && Hit.GetActor()->Implements<UPortalWallInterface>()) IsFixed = true;
		if (Counter > 30) IsFixed = true;
	}
	while (!IsFixed);

	HitToShift.Location = HitToShift.Location + Counter * 20 * DirectionVector;
}

void APortalGun::ShiftPortalPositionIfNeeded(FHitResult& FirstOffsetHit, FHitResult& SecondOffsetHit,
                                             FHitResult& PortalHit, FVector& FirstHitPosition,
                                             FVector& SecondHitPosition,
                                             FVector& Offset,
                                             ECollisionChannel CollisionChannel)
{
	if (FirstOffsetHit.GetActor() != nullptr && FirstOffsetHit.GetActor()->Implements<UPortalWallInterface>())
	{
		if (SecondOffsetHit.GetActor() == nullptr || SecondOffsetHit.GetActor() != nullptr && !SecondOffsetHit.
			GetActor()->Implements<UPortalWallInterface>())
			ShiftPortalPosition(PortalHit, SecondHitPosition, Offset, CollisionChannel);
	}
	else ShiftPortalPosition(PortalHit, FirstHitPosition, -Offset, CollisionChannel);
}

AController* APortalGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;
	return OwnerPawn->GetController();
}
