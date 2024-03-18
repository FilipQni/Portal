// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "GameFramework/Actor.h"
#include "GroundButton.generated.h"

class ASignalDotManager;
class IPickableItemInterface;
class UBoxComponent;

UCLASS()
class PORTALDEMO_API AGroundButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroundButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

	UPROPERTY(VisibleDefaultsOnly, Category="Mesh")
	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly, Category="Mesh")
	UStaticMeshComponent* MeshButton;

	UPROPERTY(VisibleDefaultsOnly, Category="Mesh")
	UStaticMeshComponent* MeshCover;

	UPROPERTY(VisibleDefaultsOnly, Category="Mesh")
	UBoxComponent* TriggerZone;
	
	UPROPERTY(EditInstanceOnly, Category="Settings")
	AInteractiveActor* ObjectToInteract;

	UPROPERTY(EditInstanceOnly, Category="Settings")
	ASignalDotManager* SignalDotManager;
	
	FVector CurrentLocation;
	bool IsOverlapped = false;
	double PressedButtonPosition; 
	double NotPressedButtonPosition;
};
