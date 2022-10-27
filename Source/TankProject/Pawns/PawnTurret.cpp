// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate , true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APawnTurret::CheckFireCondition()
{
	UE_LOG(LogTemp, Warning, TEXT("CHECK KLAPPT!"))

	if (!PlayerPawn)
	{
		return;
	}
	if(ReturnDistanceToPlayer() <= FireRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("FIRE!!!"))
	}
}


	
float APawnTurret::ReturnDistanceToPlayer()
{
	if(!PlayerPawn)
	{
		return 0;
	}
	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

