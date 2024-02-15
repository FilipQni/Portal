// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "Interactive.h"
#include "DisablingPortalZone.generated.h"

class UBoxComponent;
class APortalManager;

UCLASS()
class PORTALDEMO_API ADisablingPortalZone : public AInteractive, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADisablingPortalZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void ReactToInteraction() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(VisibleAnywhere, Category="Mesh")
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UBoxComponent* TriggerZone;

	FVector UndergroundLocation = FVector(1650.000000,-1150.000000,-600.000000);
	FVector StartingLocation;
	bool IsActive;
	APortalManager* PortalManager;
};
