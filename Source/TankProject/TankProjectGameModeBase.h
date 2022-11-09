// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankProjectGameModeBase.generated.h"

class APawnTank;
class APawnTurret;
class APlayerControllerBase;

UCLASS()
class TANKPROJECT_API ATankProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


private:
	APawnTank* PlayerTank;
	APlayerControllerBase* PlayerControllerBaseRef;
	int32 TargetTurrets = 0; //Anzahl der zu zerstörenden Turrets0
	
	int32 GetTurretAmount();
	
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

public:
	void ActorDied(AActor* DeadActor);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
	
};
