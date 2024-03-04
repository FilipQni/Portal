// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SignalDot.generated.h"

UCLASS()
class PORTALDEMO_API ASignalDot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASignalDot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void TurnOn();
	void TurnOff();
	int GetId() const;

private:
	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UMaterial* DotOnMaterial;

	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UMaterial* DotOffMaterial;

	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, Category="Settings")
	int Id;
};
