// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UMaterial;

DECLARE_DELEGATE_OneParam(FPortalOverlapDelegate, AActor*);

UCLASS()
class PORTALDEMO_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();
	APortal(const FVector* Location);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FPortalOverlapDelegate OnOverlapDelegate;


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
	UMaterial* OnMaterial;

	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UMaterial* OffMaterial;

	FVector RightVector;
	FVector ScreenCaptureLocation;

	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	void Activate() const;
	void Deactivate() const;
	void SetupRightVector();
	void SetScreenCaptureLocation(FVector NewScreenCaptureLocation);
	FVector GetDefaultScreenCaptureLocation() const;
	FVector GetRightVector() const;

};
