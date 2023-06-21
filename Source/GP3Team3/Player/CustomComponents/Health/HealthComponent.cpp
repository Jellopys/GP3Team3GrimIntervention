// Richard Hill


#include "HealthComponent.h"

#include "GP3Team3/GameEssentials/GrimGameInstance.h"
#include "GP3Team3/GameEssentials/GrimGameMode.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	ImmunityCountDown = ImmunityTime;
	GrimGameInstance = Cast<UGrimGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GrimGameMode = Cast<AGrimGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	if (bIsPlayer)
	{
		CurrentHealth = GrimGameInstance->PlayerStats->MaxHealth;
	}
	else
	{
		CurrentHealth = MaxHealth;
	}
		
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	HandleImmunityTimer(DeltaTime);
}

void UHealthComponent::HandleImmunityTimer(float DeltaTime)
{
	if (!bIsImmune) return;
	if (bIsDead) return;
	
	ImmunityCountDown -= DeltaTime;
	if (ImmunityCountDown <= 0)
	{
		bIsImmune = false;
		ImmunityCountDown = ImmunityTime; 
	}
}

void UHealthComponent::TakeDamageInternal(float IncomingHealth)
{
	TakeDamage(IncomingHealth, false);
}

void UHealthComponent::TakeDamage(float IncomingHealth, bool IsCritHit = false)
{
	if (bIsImmune) return;

	if (bIsPlayer)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - IncomingHealth, 0, GrimGameInstance->PlayerStats->MaxHealth);
		bIsImmune = true;
	}
	else
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - IncomingHealth, 0, MaxHealth);
	}
	
	OnHit.Broadcast(IncomingHealth, IsCritHit);
	
	if (CurrentHealth <= 0)
	{
		Death();
	}
}

void UHealthComponent::GainHealth(int IncomingHealth)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + IncomingHealth, 0, GrimGameInstance->PlayerStats->MaxHealth);
}

bool UHealthComponent::GetIsImmune()
{
	return bIsImmune;
}

void UHealthComponent::Death()
{
	if (bIsDead) return;
	bIsDead = true;
	if (!bIsPlayer) // If enemy dies
	{
		OnDeath.Broadcast();
		// Owner->Destroy();
	}
	else // if Player dies
	{
		GrimGameMode->AddCurrencyToMeta();
		
		APlayerCharacter* PlayerRef = Cast<APlayerCharacter>(Owner);
		PlayerRef->OnPlayerDeath();
		PlayerRef->PlayAnimationMontage(DeathMontage, 1, NAME_None);
		PlayerRef->SetCanMove(false);
	}
}

void UHealthComponent::DashImmunity(bool EnableImmunity)
{
	if (EnableImmunity)
	{
		ImmunityCountDown = 9999;
	}
	else
	{
		ImmunityCountDown = 0;
	}
	bIsImmune = EnableImmunity;
}

bool UHealthComponent::GetIsDead()
{
	return bIsDead;
}
