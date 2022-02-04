// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComponent);

	MovementSpeed = 10.f;

	TurnSpeed = 10.f;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	Controller = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller)
	{
		FHitResult HitResult;
		Controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(FName("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float value)
{
	//UE_LOG(LogTemp, Warning, TEXT("MovingForward"));
	FVector DeltaLocation(0.f, 0.f, 0.f);
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaLocation.X = value * DeltaTime * MovementSpeed;

	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Turning"));
	FRotator DeltaRotation(0.f, 0.f, 0.f);
	DeltaRotation.Yaw = value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnSpeed;

	AddActorLocalRotation(DeltaRotation);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}
