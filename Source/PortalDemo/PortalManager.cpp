// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalManager.h"
#include "PlayerCharacter.h"
#include "Portal.h"
#include "Engine/SceneCapture2D.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortalManager::APortalManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PortalEnter = nullptr;
	PortalExit = nullptr;
	IsActive = true;
}

// Called when the game starts or when spawned
void APortalManager::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetPawn());

	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TArray<AActor*> SceneCaptureActors;
	UGameplayStatics::GetAllActorsOfClass(this, ASceneCapture2D::StaticClass(), SceneCaptureActors);
	if (SceneCaptureActors.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASceneCapture2D number: %d"), SceneCaptureActors.Num());
		PortalEnterSceneCapture = Cast<ASceneCapture2D>(SceneCaptureActors[0]);
		PortalExitSceneCapture = Cast<ASceneCapture2D>(SceneCaptureActors[1]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR: ASceneCapture2D WERE NOT FOUND"));
	}

}

// Called every frame
void APortalManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PortalEnter && PortalExit)
	{
		MoveAndRotateSceneCapture(PortalExitSceneCapture, PortalEnterSceneCapture, PortalEnter, PortalExit);
		MoveAndRotateSceneCapture(PortalEnterSceneCapture, PortalExitSceneCapture, PortalExit, PortalEnter);
	}
}

void APortalManager::CreatePortalEnter(const FHitResult& Hit)
{
	if(IsActive)
	{
		if (PortalEnter != nullptr)
			PortalEnter->Destroy();

		const FRotator PortalRotation = Hit.ImpactNormal.Rotation();
		PortalEnter = GetWorld()->SpawnActor<APortal>(PortalEnterClass, Hit.Location, PortalRotation, SpawnParams);
		ActivatePortals();
		PortalEnter->SetupRightVector();
		PortalEnter->OnOverlapDelegate.BindUObject(this, &APortalManager::TeleportTargetToExit);
	}
}

void APortalManager::CreatePortalExit(const FHitResult& Hit)
{
	if(IsActive)
	{
		if (PortalExit != nullptr)
			PortalExit->Destroy();

		const FRotator PortalRotation = Hit.ImpactNormal.Rotation();
		PortalExit = GetWorld()->SpawnActor<APortal>(PortalExitClass, Hit.Location, PortalRotation, SpawnParams);
		ActivatePortals();
		PortalExit->SetupRightVector();
		PortalExit->OnOverlapDelegate.BindUObject(this, &APortalManager::TeleportTargetToEnter);
	}
}

void APortalManager::DestroyPortals() const
{
	if (PortalEnter != nullptr)
		PortalEnter->Destroy();
	if (PortalExit != nullptr)
		PortalExit->Destroy();
}

void APortalManager::Activate()
{
	this->IsActive = true;
}

void APortalManager::Deactivate()
{
	this->IsActive = false;
}

void APortalManager::ActivatePortals() const
{
	if (PortalEnter && PortalExit)
	{
		PortalEnter->Activate();
		PortalExit->Activate();

		FVector PortalLocationEnter = PortalEnter->GetActorLocation();
		FRotator PortalRotationEnter = PortalEnter->GetActorRotation();

		FVector NewPortalEnterSceneCaptureLocation = PortalLocationEnter + PortalRotationEnter.Vector() * 100.0;

		PortalEnterSceneCapture->SetActorLocation(NewPortalEnterSceneCaptureLocation);
		PortalEnterSceneCapture->SetActorRotation(PortalRotationEnter);
		PortalEnter->SetScreenCaptureLocation(NewPortalEnterSceneCaptureLocation);

		FVector PortalLocationExit = PortalExit->GetActorLocation();
		FRotator PortalRotationExit = PortalExit->GetActorRotation();

		FVector NewPortalExitSceneCaptureLocation = PortalLocationExit + PortalRotationExit.Vector() * 100.0;

		PortalExitSceneCapture->SetActorLocation(NewPortalExitSceneCaptureLocation);
		PortalExitSceneCapture->SetActorRotation(PortalRotationExit);
		PortalExit->SetScreenCaptureLocation(NewPortalExitSceneCaptureLocation);
	}
}

void APortalManager::TeleportTargetToExit(float* CaughtPlayerVelocity)
{
	Teleport(CaughtPlayerVelocity, PortalEnter, PortalExit);
}

void APortalManager::TeleportTargetToEnter(float* CaughtPlayerVelocity)
{
	Teleport(CaughtPlayerVelocity, PortalExit, PortalEnter);
}

void APortalManager::Teleport(float* CaughtPlayerVelocity, APortal* EntryPortal, APortal* ExitPortal)
{
	PlayerCharacter->SetActorLocation(ExitPortal->GetDefaultScreenCaptureLocation(), false, nullptr,
	                                  ETeleportType::TeleportPhysics);
	RotateCharactersVelocity(ExitPortal, CaughtPlayerVelocity);
	RotateCharacterAfterTeleportation(EntryPortal, ExitPortal);
	ExitPortal->Deactivate();
}

void APortalManager::MoveAndRotateSceneCapture(ASceneCapture2D* PortalSceneCaptureToRotate,
                                               ASceneCapture2D* SecondPortalSceneCapture, APortal* MainPortal,
                                               APortal* SecondPortal)
{
	//Rotation part
	FVector VectorToCharacter = PlayerCharacter->GetActorLocation() - SecondPortalSceneCapture->GetActorLocation();
	VectorToCharacter.Normalize();
	float DotProduct = FVector::DotProduct(MainPortal->GetRightVector(), VectorToCharacter) * 0.8;
	float AngleInRadians = FMath::RadiansToDegrees(DotProduct);
	FRotator PortalEnterSceneCaptureRotation = SecondPortal->GetActorForwardVector().Rotation();
	PortalEnterSceneCaptureRotation.Yaw += AngleInRadians;
	PortalSceneCaptureToRotate->SetActorRotation(PortalEnterSceneCaptureRotation);

	//TODO: SceneCapture Movement
	/*FVector DistanceToCharacter = PlayerCharacter->GetActorLocation() - MainPortal->GetDefaultScreenCaptureLocation();
	float DotProduct2 = FVector::DotProduct(MainPortal->GetActorForwardVector(), SecondPortal->GetActorForwardVector());
	float AngleInRadians2 = FMath::Acos(DotProduct2);
	float AngleInDegrees = FMath::RadiansToDegrees(AngleInRadians2);
	DistanceToCharacter = DistanceToCharacter.RotateAngleAxisRad(AngleInDegrees, FVector::ZAxisVector);
	PortalSceneCaptureToRotate->SetActorLocation(SecondPortal->GetDefaultScreenCaptureLocation() + DistanceToCharacter);
	UE_LOG(LogTemp, Warning, TEXT("Kąt pomiędzy portalami: %f, forwardWektorEnter: (%f, %f, %f), forwardWektorExit: (%f, %f, %f)"),
		AngleInDegrees, MainPortal->GetActorForwardVector().X, MainPortal->GetActorForwardVector().Y,MainPortal->GetActorForwardVector().Z,
		SecondPortal->GetActorForwardVector().X,SecondPortal->GetActorForwardVector().Y,SecondPortal->GetActorForwardVector().Z);*/
}

void APortalManager::RotateCharacterAfterTeleportation(APortal* EntryPortal, APortal* ExitPortal)
{
	const FRotator EntryVec = EntryPortal->GetActorRotation();
	const FRotator ExitVec = ExitPortal->GetActorRotation();
	const float Result = EntryVec.Yaw - ExitVec.Yaw;

	const float Dot = FVector::DotProduct(
		EntryPortal->GetActorForwardVector(), ExitPortal->GetActorForwardVector());

	if ( -0.01 < Dot && Dot < 0.01f)
	{
		float Rotation = Result;
		PlayerCharacter->RotateCharacter(Rotation);
	}
	else if (0.99 < Dot && Dot < 1.01f)
	{
		float Rotation = 180.0f;
		PlayerCharacter->RotateCharacter(Rotation);
	}
}

void APortalManager::RotateCharactersVelocity(APortal* ExitPortal, float* CaughtPlayerVelocity)
{
	float NewSpeed = *CaughtPlayerVelocity;
	FVector NewVelocity = ExitPortal->GetActorForwardVector() * NewSpeed;
	PlayerCharacter->LaunchCharacter(NewVelocity, true, true);
	DrawDebugDirectionalArrow(GetWorld(), ExitPortal->GetActorLocation(), ExitPortal->GetActorLocation() + ExitPortal->GetActorForwardVector() * NewSpeed, 2, FColor::Red, true, 5);
}
