// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckboxPlate.generated.h"

UCLASS()
class PORTALDEMO_API ACheckboxPlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckboxPlate();
	void TurnOn() const;
	void TurnOff() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UMaterial* CheckboxOnMaterial;

	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UMaterial* CheckboxOffMaterial;

	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UStaticMeshComponent* Mesh;
};
