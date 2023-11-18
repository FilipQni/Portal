// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalGun.generated.h"

class APortalManager;

UCLASS()
class PORTALDEMO_API APortalGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CreatePortalEnter();
	void CreatePortalExit();

private:
	bool Shot(FHitResult &Hit);
	bool PortalGunTrace(FHitResult& Hit, FVector& ShotDirection);
	AController* APortalGun::GetOwnerController() const;

	UPROPERTY(EditAnywhere)
	float MaxRange = 30000;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Classes")
    TSubclassOf<APortalManager> PortalManagerClass;
    	
	UPROPERTY()
	APortalManager* PortalManager;
};
