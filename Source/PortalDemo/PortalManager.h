// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalManager.generated.h"

class APortal;
class UWorld;
class ASceneCapture2D;
class APlayerCharacter;

UCLASS()
class PORTALDEMO_API APortalManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CreatePortalEnter(const FHitResult& Hit);
	void CreatePortalExit(const FHitResult& Hit);

private:
	UPROPERTY()
	APortal* PortalEnter;
	UPROPERTY()
	APortal* PortalExit;

	UPROPERTY(EditDefaultsOnly, Category="Portals")
	TSubclassOf<APortal> PortalEnterClass;

	UPROPERTY(EditDefaultsOnly, Category="Portals")
	TSubclassOf<APortal> PortalExitClass;

	FActorSpawnParameters SpawnParams;
	ASceneCapture2D* PortalEnterSceneCapture;
	ASceneCapture2D* PortalExitSceneCapture;
	APlayerCharacter* PlayerCharacter;

	void CreatePortal();
	void TeleportTargetToExit(AActor* ActorToTeleport);
	void TeleportTargetToEnter(AActor* ActorToTeleport);
	void Teleport(AActor* ActorToTeleport, APortal* EntryPortal, APortal* ExitPortal);
	void MoveAndRotateSceneCapture(ASceneCapture2D* PortalSceneCaptureToRotate, ASceneCapture2D* SecondPortalSceneCapture, APortal* MainPortal, APortal* SecondPortal);
	void RotateCharacterAfterTeleportation(AActor* Player, APortal* EntryPortal, APortal* ExitPortal);
};
