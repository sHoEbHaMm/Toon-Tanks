// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameModeBase.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxHealth = 100.f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	ToonTanksGM = Cast<AToonTanksGameModeBase>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0) return;

	if (Health <= 0)
	{
		if (ToonTanksGM)
		{
			ToonTanksGM->ActorDied(DamagedActor);
		}
	}
	
	Health -= Damage;

}

