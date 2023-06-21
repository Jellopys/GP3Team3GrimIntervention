#include "LootSpawner.h"

ALootSpawner::ALootSpawner()
{
}

void ALootSpawner::SpawnLoot()
{
	OnLootSpawned();
}

void ALootSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

