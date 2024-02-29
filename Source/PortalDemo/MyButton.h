// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "MyButton.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class PORTALDEMO_API AMyButton : public AInteractiveActor
{
	GENERATED_BODY()

public:
	AMyButton();
	virtual void ReactToInteraction() override;
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category="Mesh")
	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly, Category="Mesh")
	UStaticMeshComponent* MeshButton;

	UPROPERTY(VisibleDefaultsOnly, Category="Mesh")
	UStaticMeshComponent* MeshStand;

	UPROPERTY(VisibleDefaultsOnly, Category="Mesh")
	UStaticMeshComponent* MeshBase;

	UPROPERTY(EditInstanceOnly, Category="Settings")
	AInteractiveActor* ObjectToInteract;
};
