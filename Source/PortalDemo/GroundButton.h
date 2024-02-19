// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactive.h"
#include "GameFramework/Actor.h"
#include "GroundButton.generated.h"

class IInteractInterface;
class UBoxComponent;

UCLASS()
class PORTALDEMO_API AGroundButton : public AInteractive
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
	UPROPERTY(VisibleAnywhere, Category="Mesh")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* MeshButton;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* MeshCover;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UBoxComponent* TriggerZone;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditInstanceOnly, Category="Settings")
	AInteractive* ObjectToInteract;
	
	FVector CurrentLocation;
	bool IsOverlapped = false;
	double PressedButtonPosition; 
	double NotPressedButtonPosition;
};
