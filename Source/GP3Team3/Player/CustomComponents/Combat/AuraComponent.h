#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GP3Team3/Enemy/BaseEnemy.h"
#include "AuraComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDamaged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAuraGet);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP3TEAM3_API UAuraComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAuraComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Variables")
	bool bHasAura;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* AuraHitbox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Variables")
	float AuraIntervalTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Variables")
	int BaseDamage;

	UPROPERTY()
	TArray<TObjectPtr<ABaseEnemy>> RelevantEnemies;

	UFUNCTION(BlueprintCallable)
	void OnAuraUnlocked();
	
	UPROPERTY(BlueprintAssignable, Category="Aura")
	FOnEnemyDamaged OnEnemyDamaged;
	UPROPERTY(BlueprintAssignable, Category="Aura")
	FOnEnemyDamaged OnAuraGet;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	AActor* Owner;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	TArray<TObjectPtr<ABaseEnemy>> EnemiesToRemove;

	float InnerTimer = .0f;
 	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
