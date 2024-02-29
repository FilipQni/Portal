// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "GameFramework/Actor.h"
#include "DisablingPortalZoneManager.generated.h"

class ADisablingPortalZone;

UCLASS()
class PORTALDEMO_API ADisablingPortalZoneManager : public AInteractiveActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADisablingPortalZoneManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ReactToInteraction() override;

private:
	void CreateDisablingPortalZone();

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<ADisablingPortalZone> DisablingPortalZoneClass;

	UPROPERTY(EditInstanceOnly, Category="Settings")
	ADisablingPortalZone* DisablingPortalZone;
	
	FVector DisPortalZonePosition;
	FVector DisPortalZoneScale;
	FRotator DisPortalZoneRotation;
};
