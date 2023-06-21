// Richard Hill

#pragma once

#include "Components/ActorComponent.h"
#include "GP3Team3/Player/PlayerStats.h"
#include "HealthComponent.generated.h"

class UGrimGameInstance;
class UPlayerStatsObject;
class AGrimGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FComponentCustomStartSignature, float, DamageAmount, bool, CritDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(meta=(BlueprintSpawnableComponent))
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float CurrentHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health")
	float ImmunityTime = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health")
	bool bIsPlayer = false;
	
	void TakeDamageInternal(float IncomingHealth);
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float IncomingHealth, bool IsCritHit);

	UPROPERTY(BlueprintAssignable, Category="Health")
	FComponentCustomStartSignature OnHit;

	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnDeath OnDeath;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* DeathMontage;
	
	UFUNCTION(BlueprintCallable)
	void GainHealth(int IncomingHealth);

	UFUNCTION()
	bool GetIsImmune();

	UFUNCTION(BlueprintCallable)
	void Death();

	UFUNCTION()
	void DashImmunity(bool EnableImmunity);

	UFUNCTION()
	bool GetIsDead();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	AActor* Owner;

	UPROPERTY()
	UGrimGameInstance* GrimGameInstance;
	UPROPERTY()
	AGrimGameMode* GrimGameMode;

	UPROPERTY()
	float ImmunityCountDown;
	UPROPERTY(BlueprintReadOnly)
	bool bIsImmune;
	UPROPERTY(BlueprintReadOnly)
	bool bIsDead;

	UFUNCTION()
	void HandleImmunityTimer(float DeltaTime);
};
