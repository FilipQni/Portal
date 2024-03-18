// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UMaterial;

DECLARE_DELEGATE_OneParam(FPortalOverlapDelegate, float*);

UCLASS()
class PORTALDEMO_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	APortal();
	APortal(const FVector* Location);

protected:
	virtual void BeginPlay() override;

public:	
	FPortalOverlapDelegate OnOverlapDelegate;
	
	virtual void Tick(float DeltaTime) override;
	void Activate();
	bool IsActive();
	void SetActive();
	void Deactivate();
	void SetupRightVector();
	void SetScreenCaptureLocation(FVector NewScreenCaptureLocation);
	FVector GetDefaultScreenCaptureLocation() const;
	FVector GetRightVector() const;
	

private:
	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* MeshBase;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* MeshPortal;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UBoxComponent* TriggerZone;

	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UBoxComponent* CatchVelocityZone;

	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UMaterial* OnMaterial;

	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UMaterial* OffMaterial;

	FVector RightVector;
	FVector ScreenCaptureLocation;
	bool Active;
	float CaughtPlayerVelocity;
	float TriggerZoneCooldown = 0.2f;
	float LastTriggerActivationTime = 0.0f;

	UFUNCTION()
	void TeleportPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void CatchPlayerVelocity(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
