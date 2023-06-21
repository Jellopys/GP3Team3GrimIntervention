// Fill out your copyright notice in the Description page of Project Settings.


#include "Sector.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ASector::ASector()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = SceneRoot;
}

void ASector::Collapse()
{
	if(PossibleTileClasses.Num() == 0)
	{
		PossibleTileClasses.Add(NullTileClass);
	}

	int IndexPicker = FMath::RandRange(0, PossibleTileClasses.Num()-1);

	GeneratedTileClass = PossibleTileClasses[IndexPicker];
	
	GeneratedTile = GetWorld()->SpawnActor<ATileBase>(PossibleTileClasses[IndexPicker], GetActorLocation(), FRotator(0, 0, 0));

	GeneratedTile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

	GeneratedTile->XPos = XPos;
	GeneratedTile->YPos = YPos;
}

void ASector::Collapse(TSubclassOf<ATileBase> SpawnTileClass)
{
	GeneratedTileClass = SpawnTileClass;
	
	GeneratedTile = GetWorld()->SpawnActor<ATileBase>(SpawnTileClass, GetActorLocation(), FRotator(0, 0, 0));

	GeneratedTile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

	GeneratedTile->XPos = XPos;
	GeneratedTile->YPos = YPos;
}

void ASector::FilterPossibleList(TArray<ETileType> TileTypesToKeep, TObjectPtr<ASector> PreviousSector)
{
	TSubclassOf<ATileBase> PreviousTileClass = PreviousSector->GeneratedTileClass;
	
	for (int32 Index = PossibleTileClasses.Num()-1; Index >= 0; --Index)
	{
		ATileBase* TempTile = Cast<ATileBase>(PossibleTileClasses[Index]->GetDefaultObject());
		if(!TileTypesToKeep.Contains(TempTile->ThisTileType))
		{
			PossibleTileClasses.RemoveAt(Index);
		}
		else if(PossibleTileClasses[Index] == PreviousTileClass)
		{
			PossibleTileClasses.RemoveAt(Index);
		}
	}
}

// Called when the game starts or when spawned
void ASector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

