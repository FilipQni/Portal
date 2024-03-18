// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "PortalDemo/Player/PlayerCharacter.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	MeshBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	MeshBase->SetupAttachment(Root);

	MeshPortal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Portal"));
	MeshPortal->SetupAttachment(Root);

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Zone"));
	TriggerZone->SetupAttachment(Root);

	CatchVelocityZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Catch Velocity Zone"));
	CatchVelocityZone->SetupAttachment(Root);
}

APortal::APortal(const FVector* Location)
{
	this->SetActorLocation(*Location);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
	Active = false;
	MeshPortal->SetMaterial(0,OffMaterial);
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &APortal::TeleportPlayer);
	CatchVelocityZone->OnComponentBeginOverlap.AddDynamic(this, &APortal::CatchPlayerVelocity);

	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::Activate()
{
	MeshPortal->SetMaterial(0, OnMaterial);
	Active = true;
}

bool APortal::IsActive()
{
	return Active;
}

void APortal::SetActive()
{
	Active = true;
}

void APortal::Deactivate()
{
	MeshPortal->SetMaterial(0, OffMaterial);
	Active = false;
}

FVector APortal::GetRightVector() const
{
	return RightVector;
}

void APortal::SetupRightVector()
{
	FRotator const YawRotation(0, 90, 0);
	RightVector = YawRotation.RotateVector(GetActorForwardVector());
}

void APortal::SetScreenCaptureLocation(FVector NewScreenCaptureLocation)
{
	ScreenCaptureLocation = NewScreenCaptureLocation;
}

FVector APortal::GetDefaultScreenCaptureLocation() const
{
	return ScreenCaptureLocation;
}

void APortal::CatchPlayerVelocity(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Active && OtherActor->GetName() == "BP_PlayerCharacter_C_0")
	{
		FVector Test = OtherActor->GetVelocity();
		CaughtPlayerVelocity = Test.Size();
		UE_LOG(LogTemp, Warning, TEXT("Vector speed: %s,  Speed: %f"), *Test.ToString(), CaughtPlayerVelocity);
	}
}

void APortal::TeleportPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Active && OtherActor->IsA<APlayerCharacter>())
	{
		float CurrentTime = GetWorld()->GetTimeSeconds();
		if (CurrentTime - LastTriggerActivationTime >= TriggerZoneCooldown)
		{
			OnOverlapDelegate.ExecuteIfBound(&CaughtPlayerVelocity);
			LastTriggerActivationTime = CurrentTime;
		}
		
	}
}


