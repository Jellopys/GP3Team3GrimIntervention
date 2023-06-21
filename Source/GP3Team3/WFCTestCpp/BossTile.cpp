// Fill out your copyright notice in the Description page of Project Settings.


#include "BossTile.h"


// Sets default values
ABossTile::ABossTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SceneRoot->SetupAttachment(RootComponent);
	
	BridgeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bridge Mesh Component"));
	BridgeMeshComponent->SetupAttachment(SceneRoot);
	
	FightAreaMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fight Area Mesh Component"));
	FightAreaMeshComponent->SetupAttachment(SceneRoot);
	
	NiagaraBossDoor = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Boss Door"));
	NiagaraBossDoor->SetupAttachment(SceneRoot);

	BossBlocker1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Boss Block Wall 1"));
	BossBlocker1->SetupAttachment(SceneRoot);
	BossBlocker2= CreateDefaultSubobject<UBoxComponent>(TEXT("Boss Block Wall 2"));
	BossBlocker2->SetupAttachment(SceneRoot);
	BossBlocker3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Boss Block Wall 3"));
	BossBlocker3->SetupAttachment(SceneRoot);
	BossBlocker4 = CreateDefaultSubobject<UBoxComponent>(TEXT("Boss Block Wall 4"));
	BossBlocker4->SetupAttachment(SceneRoot);
	BossBlocker5 = CreateDefaultSubobject<UBoxComponent>(TEXT("Boss Block Wall 5"));
	BossBlocker5->SetupAttachment(SceneRoot);
}

void ABossTile::OpenBossRoom()
{
	OnBossRoomOpen();
}

// Called when the game starts or when spawned
void ABossTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

