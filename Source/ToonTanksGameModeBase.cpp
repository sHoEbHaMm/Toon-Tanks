// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameModeBase::ActorDied(AActor* DiedActor)
{
	TargetTowers = GetTargetTowers();

	if (Tank == DiedActor)
	{
		Tank->HandleDestruction();

		if(ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATurret* Turret = Cast<ATurret>(DiedActor))
	{
		Turret->HandleDestruction();
		--TargetTowers;
		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameModeBase::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;

		FTimerDelegate Delegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, Delegate, StartDelay, false);
	}
}

int32 AToonTanksGameModeBase::GetTargetTowers()
{
	TArray<AActor*> TurretArray;

	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), TurretArray);

	int32 Num = TurretArray.Num();
	return Num;
}
