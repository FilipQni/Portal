// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SignalDotManager.generated.h"

class ACheckboxPlate;
class ASignalDot;

UCLASS()
class PORTALDEMO_API ASignalDotManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASignalDotManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Interact();

private:
	UPROPERTY(EditInstanceOnly, Category="Settings")
	int Id;

	UPROPERTY(EditInstanceOnly, Category="Settings")
	ACheckboxPlate* CheckboxPlate;
	
	bool bActive;
	TArray<ASignalDot*> DotsArray;
};
