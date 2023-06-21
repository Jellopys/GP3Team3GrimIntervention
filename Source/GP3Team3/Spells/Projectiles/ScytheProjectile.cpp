// Fill out your copyright notice in the Description page of Project Settings.


#include "ScytheProjectile.h"

#include "Components/SphereComponent.h"
#include "CollisionShape.h"
#include "GP3Team3/Player/PlayerCharacter.h"

class UHealthComponent;

AScytheProjectile::AScytheProjectile()
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

void AScytheProjectile::BeginPlay()
{
	Super::BeginPlay();
	OnActive();
}

void AScytheProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsActive) return;

	if (!bReturnScythe)
	{
		MoveProjectile(DeltaTime);
	}
	else
	{
		ReturnScythe(DeltaTime);
	}
}

void AScytheProjectile::ReturnScythe(float DeltaTime)
{
	if (!Parent) return;
	

	TravelDelta += DeltaTime * TravelSpeed;
	
	FVector Loc = FMath::Lerp(GetActorLocation(), Parent->GetActorLocation(), TravelDelta / TravelDistance);
	
	SetActorLocation(Loc);
	
	if ((GetActorLocation() - Parent->GetActorLocation()).Length() <= StopDistance)
	{
		PlayerRef->OnReturnScythe();
		SetActiveStatus(false);
	}
}

void AScytheProjectile::AssignParent(AActor* NewParent)
{
	Parent = NewParent;
	PlayerRef = Cast<APlayerCharacter>(Parent);
}

void AScytheProjectile::MoveProjectile(float DeltaTime)
{
	TravelDelta += DeltaTime * TravelSpeed;
	
	SetActorLocation(FMath::Lerp(GetActorLocation(), TargetLocation, TravelDelta / TravelDistance));
	
	if ((GetActorLocation() - TargetLocation).Length() <= StopDistance)
	{
		TravelDelta = 0;
		bReturnScythe = true;
		OnScytheReachApex();
	}
}

void AScytheProjectile::SetActiveStatus(bool SetActive)
{
	if (SetActive)
	{
		if (bIsActive) return;
		
		SetActorLocation(PlayerRef->GetActorLocation() + PlayerRef->GetActorForwardVector() * ScytheForwardSpawnLoc);
		bIsActive = true;
		TargetLocation = PlayerRef->GetActorLocation() + PlayerRef->GetActorForwardVector() * TravelDistance;
		UE_LOG(LogTemp,Warning,TEXT("TargetLocation is : %s"), *TargetLocation.ToString());
		bReturnScythe = false;
		TravelDelta = 0;
		OnScytheCast();
		SetActorHiddenInGame(false);
	}
	else
	{
		bIsActive = false;
		OnScytheReturn();
		SetActorHiddenInGame(true);
	}
}





