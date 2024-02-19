// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundButton.h"

#include "InteractInterface.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGroundButton::AGroundButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	MeshButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Mesh"));
	MeshButton->SetupAttachment(Root);

	MeshCover = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cover Mesh"));
	MeshCover->SetupAttachment(Root);

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger zone"));
	TriggerZone->SetupAttachment(MeshButton);
}

// Called when the game starts or when spawned
void AGroundButton::BeginPlay()
{
	Super::BeginPlay();

	if (ObjectToInteract == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Ground button has no %s Object to Interact"), *this->GetName());

	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AGroundButton::OnOverlapBegin);
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &AGroundButton::OnOverlapEnd);

	NotPressedButtonPosition = MeshButton->GetRelativeLocation().Z;
	PressedButtonPosition = NotPressedButtonPosition - 10;
}

// Called every frame
void AGroundButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsOverlapped)
	{
		if (MeshButton->GetRelativeLocation().Z > PressedButtonPosition)
		{
			CurrentLocation = MeshButton->GetRelativeLocation();
			CurrentLocation.Z -= 1;
			MeshButton->SetRelativeLocation(CurrentLocation);
		}
	}
	else
	{
		if (MeshButton->GetRelativeLocation().Z < NotPressedButtonPosition)
		{
			CurrentLocation = MeshButton->GetRelativeLocation();
			CurrentLocation.Z += 1;
			MeshButton->SetRelativeLocation(CurrentLocation);
		}
	}
}

void AGroundButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	IsOverlapped = true;
	ObjectToInteract->ReactToInteraction();
}

void AGroundButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IsOverlapped = false;
}
