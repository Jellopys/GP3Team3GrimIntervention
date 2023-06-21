// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSpawner.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ATileSpawner::ATileSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATileSpawner::GenerateGrid(const FVector CenteredLocation, const int X, const int Y, const float TileSpacing)
{
	ASector* EmptySector;
	GridSectors.Init({EmptySector}, X, Y);

	GridSize.X = X;
	GridSize.Y = Y;

	for (auto OuterIndex{0}; OuterIndex <= X - 1; OuterIndex++)
	{
		TArray<TObjectPtr<ASector>> NewArrayToAdd;
		for (auto InnerIndex{0}; InnerIndex <= Y - 1; InnerIndex++)
		{
			FVector SpawnLocation = FVector(static_cast<float>(InnerIndex) - static_cast<float>(X) / 2.f,
			                                static_cast<float>(OuterIndex) - static_cast<float>(Y) / 2.f, 0.f)
				* TileSpacing * 1.f + CenteredLocation;
			
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SpawnLocation);

			if (SectorClass)
			{
				AActor* NewSector = UGameplayStatics::BeginDeferredActorSpawnFromClass(
					this, SectorClass, SpawnTransform);

				NewSector->FinishSpawning(SpawnTransform);
				NewSector->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

				ASector* Sector = Cast<ASector>(NewSector);

				Sector->PossibleTileClasses = AllTileClasses;
				Sector->XPos = OuterIndex;
				Sector->YPos = InnerIndex;
				GridSectors.SetElement(OuterIndex, InnerIndex, Sector);
			}
		}
	}
}

void ATileSpawner::CollapseFirstTile()
{
	int RandomIndexX = 4;
	int RandomIndexY = 9;
	
	ASector* TempSector = Cast<ASector>(GridSectors.GetElement(RandomIndexX, RandomIndexY));

	TempSector->Collapse(SpawnTileClass);

	BossTile = GetWorld()->SpawnActor<ABossTile>(BossTileClass, TempSector->GetActorLocation(), FRotator(0, 0, 0));
	
	BossTile->AttachToActor(TempSector, FAttachmentTransformRules::KeepRelativeTransform);

	BossTile->AddActorLocalOffset(FVector(1100, 0, 0));
	
	//up
	if (RandomIndexY != static_cast<int>(GridSize.Y) - 1)
	{
		GridSectors.GetElement(RandomIndexX, RandomIndexY + 1)->FilterPossibleList(TempSector->GeneratedTile->Up_TypeConnections, TempSector);
	}

	//down
	if (RandomIndexY != 0)
	{
		GridSectors.GetElement(RandomIndexX, RandomIndexY - 1)->FilterPossibleList(TempSector->GeneratedTile->Down_TypeConnections, TempSector);
	}
	//left
	if (RandomIndexX != 0)
	{
		GridSectors.GetElement(RandomIndexX - 1, RandomIndexY)->FilterPossibleList(TempSector->GeneratedTile->Left_TypeConnections, TempSector);
	}

	//right
	if (RandomIndexX != static_cast<int>(GridSize.X) - 1)
	{
		GridSectors.GetElement(RandomIndexX + 1, RandomIndexY)->FilterPossibleList(TempSector->GeneratedTile->Left_TypeConnections, TempSector);
	}
}

void ATileSpawner::CollapseNextTile()
{
	bool FoundNonCollapsedSector = false;

	for (auto IncrementerX{0}; IncrementerX < static_cast<int>(GridSize.X); IncrementerX++)
	{
		for (auto IncrementerY{0}; IncrementerY < static_cast<int>(GridSize.Y); IncrementerY++)
		{
			if (GridSectors.GetElement(IncrementerX, IncrementerY)->GeneratedTile == nullptr)
			{
				FoundNonCollapsedSector = true;
			}
		}
	}

	if (!FoundNonCollapsedSector)
	{
		return;
	}

	TArray<ASector*> LowestEntropySectors;
	int LowestEntropy = AllTileClasses.Num();

	for (auto IncrementerX{0}; IncrementerX < static_cast<int>(GridSize.X); IncrementerX++)
	{
		for (auto IncrementerY{0}; IncrementerY < static_cast<int>(GridSize.Y); IncrementerY++)
		{
			if (GridSectors.GetElement(IncrementerX, IncrementerY)->PossibleTileClasses.Num() <= LowestEntropy)
			{
				if(GridSectors.GetElement(IncrementerX, IncrementerY)->GeneratedTile == nullptr)
				{
					if (GridSectors.GetElement(IncrementerX, IncrementerY)->PossibleTileClasses.Num() < LowestEntropy)
					{
						LowestEntropy = GridSectors.GetElement(IncrementerX, IncrementerY)->PossibleTileClasses.Num();
						LowestEntropySectors.Empty();
						LowestEntropySectors.Add(GridSectors.GetElement(IncrementerX, IncrementerY));
					}
					else
					{
						LowestEntropySectors.Add(GridSectors.GetElement(IncrementerX, IncrementerY));
					}
				}
			}
		}
	}

	int RandomIndex = FMath::RandRange(0, LowestEntropySectors.Num() - 1);

	ASector* TempSector = LowestEntropySectors[RandomIndex];

	TempSector->Collapse();

	//up
	if (TempSector->YPos != static_cast<int>(GridSize.Y) - 1)
	{
		GridSectors.GetElement(TempSector->XPos, TempSector->YPos + 1)->FilterPossibleList(TempSector->GeneratedTile->Up_TypeConnections, TempSector);
	}

	//down
	if (TempSector->YPos != 0)
	{
		GridSectors.GetElement(TempSector->XPos, TempSector->YPos - 1)->FilterPossibleList(TempSector->GeneratedTile->Down_TypeConnections, TempSector);
	}

	//left
	if (TempSector->XPos != 0)
	{
		GridSectors.GetElement(TempSector->XPos - 1, TempSector->YPos)->FilterPossibleList(TempSector->GeneratedTile->Left_TypeConnections, TempSector);
	}

	//right
	if (TempSector->XPos != static_cast<int>(GridSize.X) - 1)
	{
		GridSectors.GetElement(TempSector->XPos + 1, TempSector->YPos)->FilterPossibleList(TempSector->GeneratedTile->Right_TypeConnections, TempSector);
	}

	CollapseNextTile();
}

// Called when the game starts or when spawned
void ATileSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
