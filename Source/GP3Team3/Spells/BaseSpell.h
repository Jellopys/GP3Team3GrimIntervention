// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpell.generated.h"

class APlayerCharacter;
struct FPlayerStats;
class UGrimGameInstance;

UCLASS()
class ABaseSpell : public AActor
{
	GENERATED_BODY()

public:
	ABaseSpell();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Activate();
	virtual void Release();
	virtual void AssignOwner(AActor* OwnerAct);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellInfo)
	FString SpellName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellInfo)
	float Cooldown = 1;
	UPROPERTY(BlueprintReadOnly, Category = SpellInfo)
	AActor* OwnerActor;
	
protected:
	float CooldownTimer = 1;

	UPROPERTY()
	UGrimGameInstance* GrimGameInstance;
	
	FPlayerStats* PlayerStats;
};
