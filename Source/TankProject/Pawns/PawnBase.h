// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraShake.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankProject/Component/HealthComponent.h"
#include "PawnBase.generated.h"


class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;
class UMatineeCameraShake;

UCLASS()
class TANKPROJECT_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();

	void RotateTurretFunction(FVector LookAtTarget);
	void Fire();
	virtual void HandleDestruction();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess= true))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess= true))
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess= true))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess= true))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile Type", meta = (AllowPrivateAccess= true))
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile Type", meta = (AllowPrivateAccess= true))
	UHealthComponent* HealthComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* DeathParticle;
	
	UPROPERTY(EditAnywhere, Category = "VFX")
	FVector VFXScale = FVector(8.0f,8.0f,8.0f);

	UPROPERTY(EditAnywhere, Category = "VFX")
	TSubclassOf<UMatineeCameraShake> ExplosionCameraShake;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	


};
