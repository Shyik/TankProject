// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "Camera/CameraShake.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->InitialSpeed = MovementSpeed;
	ProjectileMovementComponent->MaxSpeed = MovementSpeed;

	InitialLifeSpan = 3.f;
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

	ProjectileTrail = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileTrail"));
	ProjectileTrail->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if(!MyOwner)
	{
		return;
	}

	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this , DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());

		if(HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}

		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShake);
	}

	Destroy();
}


// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

