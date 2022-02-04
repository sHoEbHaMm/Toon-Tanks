// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);

	void Fire();

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditAnywhere, Category = "Components")
	class USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere)
	class USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
