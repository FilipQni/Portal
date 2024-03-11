// Fill out your copyright notice in the Description page of Project Settings.


#include "DisablingPortalZone.h"
#include "PortalManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADisablingPortalZone::ADisablingPortalZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(Root);
	
	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Zone"));
	TriggerZone->SetupAttachment(Root);

	bActive = true;
}

// Called when the game starts or when spawned
void ADisablingPortalZone::BeginPlay()
{
	Super::BeginPlay();

	PortalManager = Cast<APortalManager>(UGameplayStatics::GetActorOfClass(GetWorld(), APortalManager::StaticClass()));
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ADisablingPortalZone::OnOverlapBegin);
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &ADisablingPortalZone::OnOverlapEnd);
}

// Called every frame
void ADisablingPortalZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADisablingPortalZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PortalManager->DestroyPortals();
	PortalManager->Deactivate();
	UE_LOG(LogTemp, Warning, TEXT("DisablingPortalZone overlap begins"));
}

void ADisablingPortalZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PortalManager->Activate();
	UE_LOG(LogTemp, Warning, TEXT("DisablingPortalZone overlap ends"));
}



