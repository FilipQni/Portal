// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PortalGun.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetMesh());
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	PortalGun = GetWorld()->SpawnActor<APortalGun>(GunClass);
	PortalGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	PortalGun->SetOwner(this);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APlayerCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("CreatePortalEnter"), EInputEvent::IE_Pressed, this, &APlayerCharacter::CreatePortalEnter);
	PlayerInputComponent->BindAction(TEXT("CreatePortalExit"), EInputEvent::IE_Pressed, this, &APlayerCharacter::CreatePortalExit);
}

void APlayerCharacter::Rotate(float Angle)
{
	FRotator NewCharacterRotation = GetActorRotation() + FRotator(0.0f, Angle, 0.0f);
	GetController()->SetControlRotation(NewCharacterRotation);

	//TODO: Nadać postaci odpowiednie velocity po przejściu przez portal
	/*FVector PlayerVelocity = GetVelocity();
	FVector AdjustedVelocity = PlayerVelocity.RotateAngleAxis(PortalRotationDiff.Yaw, FVector::UpVector);
	LaunchCharacter(NewCharacterRotation, false, false);*/
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);	
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);	
}

void APlayerCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);	
}

void APlayerCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerCharacter::CreatePortalEnter()
{
	PortalGun->CreatePortalEnter();
}

void APlayerCharacter::CreatePortalExit()
{
	PortalGun->CreatePortalExit();
}

