// Copyright Epic Games, Inc. All Rights Reserved.


#include "TankProjectGameModeBase.h"
#include "Pawns/PawnTank.h"
#include "Pawns/PawnTurret.h"
#include "PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

void ATankProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Hole alle Turrets im Level
	TargetTurrets = GetTurretAmount();

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	PlayerControllerBaseRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	// Win / Lose condition, Ref var
	// Call HandleGameStart, init Countdown, pawn check
	HandleGameStart();
	
}

int ATankProjectGameModeBase::GetTurretAmount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}

void ATankProjectGameModeBase::HandleGameStart()
{
	// Start Countdown, Call Blueprint version GameStart
	GameStart();

	if(PlayerControllerBaseRef)
	{
		PlayerControllerBaseRef->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerBaseRef, &APlayerControllerBase::SetPlayerEnableState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void ATankProjectGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);

	if(PlayerControllerBaseRef)
	{
		PlayerControllerBaseRef->SetPlayerEnableState(false);
	}
}

void ATankProjectGameModeBase::ActorDied(AActor* DeadActor)
{
	// Player? > Loose!?
	//UE_LOG(LogTemp, Error, TEXT("Dead"));
	if(DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);
	}
	else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		TargetTurrets--;
		if (TargetTurrets<=0)
		{
			HandleGameOver(true);
		}
	}
}
