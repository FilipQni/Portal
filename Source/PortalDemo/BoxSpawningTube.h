// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "GameFramework/Actor.h"
#include "BoxSpawningTube.generated.h"

class AMyBox;

UCLASS()
class PORTALDEMO_API ABoxSpawningTube : public AInteractiveActor
{
	GENERATED_BODY()

public:
	ABoxSpawningTube();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* WallOneMesh;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* WallTwoMesh;
	
	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* WallThreeMesh;
	
	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* WallFourMesh;


private:
	void SpawnBox();
	
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<AMyBox> BoxClass;
	
	AMyBox* Box;
	FRotator BoxSpawnRotation;
	FVector BoxSpawnLocation;

	
};
