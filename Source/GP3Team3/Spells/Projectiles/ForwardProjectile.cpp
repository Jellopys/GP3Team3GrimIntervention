// Fill out your copyright notice in the Description page of Project Settings.


#include "ForwardProjectile.h"

#include "Components/SphereComponent.h"
#include "CollisionShape.h"
#include "GP3Team3/Enemy/BaseEnemy.h"
#include "GP3Team3/Player/CustomComponents/Health/HealthComponent.h"

class UHealthComponent;

AForwardProjectile::AForwardProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	RootComponent = Sphere;
	Sphere->SetCollisionProfileName("OverlapAllDynamic");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	Mesh->SetupAttachment(Sphere);
	Mesh->SetCollisionProfileName("NoCollision");
	Mesh->SetEnableGravity(false);
}

void AForwardProjectile::BeginPlay()
{
	Super::BeginPlay();
	OnActive();
}

void AForwardProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LifeTime += DeltaTime;
	if (LifeTime > MaxLifeTime)
	{
		SetActiveStatus(false);
	}
	else
	{
		MoveProjectile(DeltaTime);
	}
}

void AForwardProjectile::AssignParent(AActor* NewParent)
{
	Parent = NewParent;
}

void AForwardProjectile::MoveProjectile(float DeltaTime)
{
	FHitResult Hit;
	FCollisionShape SphereShape = FCollisionShape::MakeSphere(Sphere->GetScaledSphereRadius());
	FVector const ForwardMovement = GetActorForwardVector() * TravelSpeed * DeltaTime;
	Sphere->SetCollisionProfileName("NoCollision");
	// Find actors in front of the projectile
	GetWorld()->SweepSingleByChannel(Hit, GetActorLocation(),GetActorLocation() + ForwardMovement, FQuat::Identity, ECC_WorldStatic, SphereShape);
	Sphere->SetCollisionProfileName("OverlapAllDynamic");
	
	AddActorWorldOffset(ForwardMovement, false);

	if (Hit.bBlockingHit && Hit.GetActor() != nullptr)
	{
		AActor* HitActor = Hit.GetActor();
		if (Parent != nullptr && Parent == HitActor)
		{
			return;
		}
		if (Hit.GetActor()->IsA(AForwardProjectile::StaticClass()) || HitActor->IsA(ABaseEnemy::StaticClass()))
		{
			return;
		}
		if (UHealthComponent* HealthComponent = HitActor->FindComponentByClass<UHealthComponent>())
		{
			UE_LOG(LogTemp,Warning,TEXT("Projectile Hit"));
			HealthComponent->TakeDamageInternal(Damage);
		}
		if (!bIsPenetrating)
		{
			SetActiveStatus(false);
		}
	}
}

void AForwardProjectile::SetActiveStatus(bool status)
{
	OnHit();
	Destroy();
}





