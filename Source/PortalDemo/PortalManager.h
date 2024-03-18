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
	void DestroyPortals() const;
	void Activate();
	void Deactivate();

private:
	UPROPERTY()
	APortal* PortalEnter;
	UPROPERTY()
	APortal* PortalExit;

	UPROPERTY(EditDefaultsOnly, Category="Portals")
	TSubclassOf<APortal> PortalEnterClass;

	UPROPERTY(EditDefaultsOnly, Category="Portals")
	TSubclassOf<APortal> PortalExitClass;

	UPROPERTY(EditInstanceOnly, Category="Portals")
	ASceneCapture2D* PortalEnterSceneCapture;

	UPROPERTY(EditInstanceOnly, Category="Portals")
	ASceneCapture2D* PortalExitSceneCapture;
	
	FActorSpawnParameters SpawnParams;
	APlayerCharacter* PlayerCharacter;
	bool IsActive;
	
	void ActivatePortals() const;
	void TeleportTargetToExit(float* CaughtPlayerVelocity);
	void TeleportTargetToEnter(float* CaughtPlayerVelocity);
	void Teleport(float* CaughtPlayerVelocity, APortal* EntryPortal, APortal* ExitPortal);
	void MoveAndRotateSceneCapture(ASceneCapture2D* PortalSceneCaptureToRotate, ASceneCapture2D* SecondPortalSceneCapture, APortal* MainPortal, APortal* SecondPortal);
	void RotateCharacterAfterTeleportation(APortal* EntryPortal, APortal* ExitPortal);
	void RotateCharactersVelocity(APortal* ExitPortal, float* CaughtPlayerVelocity);
};
