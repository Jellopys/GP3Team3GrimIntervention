// Richard Hill

#pragma once

#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS()
class GP3TEAM3_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	AActor* Owner;
};
