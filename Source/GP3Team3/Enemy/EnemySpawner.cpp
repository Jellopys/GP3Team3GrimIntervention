#include "EnemySpawner.h"

AEnemySpawner::AEnemySpawner()
{
}

void AEnemySpawner::SpawnEnemy()
{
	OnEnemySpawned();
}

TSubclassOf<AActor> AEnemySpawner::GetRandomEnemyClass()
{
	float Index = FMath::RandRange(0, EnemyClasses.Num()-1);
	return EnemyClasses[Index];
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

