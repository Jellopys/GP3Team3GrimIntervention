#include "TileBase.h"
#include "GP3Team3/Enemy/BaseEnemy.h"
#include "GP3Team3/Enemy/EnemySpawner.h"
#include "GP3Team3/GameEssentials/GrimGameMode.h"
#include "GP3Team3/Player/PlayerCharacter.h"
#include "GP3Team3/Powerups/LootSpawner.h"

// Sets default values
ATileBase::ATileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SceneRoot->SetupAttachment(RootComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(SceneRoot);

	TileOverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Tile Overlap Box"));
	TileOverlapBox->SetupAttachment(SceneRoot);
	TileOverlapBox->SetBoxExtent(FVector(850, 850, 1500));
	
	TileEnemyInfoComponent = CreateDefaultSubobject<UTileEnemyInfo>(TEXT("Tile Enemy Info Component"));

	ArrayDictionary = new FTileTypeArrays;
}

void ATileBase::RegisterEnemyKill()
{
	NumberOfAliveEnemies--;

	if(NumberOfAliveEnemies <= 0)
	{
		GameMode->RegisterTileExploration(XPos, YPos, EExplorationState::Cleared);
		GameMode->ResetTempStats();

		SpawnLoot();
	
		if(TileEnemyInfoComponent->CanTrapUntilEnemiesKilled && WallsUp)
		{
			UpWall->Destroy();
			DownWall->Destroy();
			LeftWall->Destroy();
			RightWall->Destroy();

			GameMode->OnWallsDown();
		}
	}
}

// Called when the game starts or when spawned
void ATileBase::BeginPlay()
{
	Super::BeginPlay();

	//Game Mode
	
	AGameModeBase* TempGameMode = GetWorld()->GetAuthGameMode();
	GameMode = Cast<AGrimGameMode>(TempGameMode);

	//Enemy Spawners

	TArray<UChildActorComponent*> AllChildActorComponents;
	GetComponents<UChildActorComponent>(AllChildActorComponents);

	if(!AllChildActorComponents.IsEmpty())
	{
		for (auto Index{0}; Index <= AllChildActorComponents.Num()-1; Index++)
		{
			AActor* TempSpawner = AllChildActorComponents[Index]->GetChildActor();
			if(TempSpawner->IsA(AEnemySpawner::StaticClass()))
			{
				AEnemySpawner* TempEnemySpawner = Cast<AEnemySpawner>(TempSpawner);
				EnemySpawners.Add(TempEnemySpawner);
			}
			if(TempSpawner->IsA(ALootSpawner::StaticClass()))
			{
				ALootSpawner* TempLootSpawner = Cast<ALootSpawner>(TempSpawner);
				LootSpawners.Add(TempLootSpawner);
			}
		}
	}

	//Overlap Box
	
	TileOverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ATileBase::OnOverlapBegin);

	//Tile Type
	
	switch (ThisTileType)
	{
	case ETileType::LevelOne:
		Up_TypeConnections = ArrayDictionary->LevelOneU;
		Down_TypeConnections = ArrayDictionary->LevelOneD;
		Left_TypeConnections = ArrayDictionary->LevelOneL;
		Right_TypeConnections = ArrayDictionary->LevelOneR;
		
		break;

	case ETileType::LevelTwo:
		Up_TypeConnections = ArrayDictionary->LevelTwoU;
		Down_TypeConnections = ArrayDictionary->LevelTwoD;
		Left_TypeConnections = ArrayDictionary->LevelTwoL;
		Right_TypeConnections = ArrayDictionary->LevelTwoR;
		break;

	case ETileType::StairUp:
		Up_TypeConnections = ArrayDictionary->StairUpU;
		Down_TypeConnections = ArrayDictionary->StairUpD;
		Left_TypeConnections = ArrayDictionary->StairUpL;
		Right_TypeConnections = ArrayDictionary->StairUpR;
		break;

	case ETileType::StairDown:
		Up_TypeConnections = ArrayDictionary->StairDownU;
		Down_TypeConnections = ArrayDictionary->StairDownD;
		Left_TypeConnections = ArrayDictionary->StairDownL;
		Right_TypeConnections = ArrayDictionary->StairDownR;
		break;

	case ETileType::StairLeft:
		Up_TypeConnections = ArrayDictionary->StairLeftU;
		Down_TypeConnections = ArrayDictionary->StairLeftD;
		Left_TypeConnections = ArrayDictionary->StairLeftL;
		Right_TypeConnections = ArrayDictionary->StairLeftR;
		
		break;

	case ETileType::StairRight:
		Up_TypeConnections = ArrayDictionary->StairRightU;
		Down_TypeConnections = ArrayDictionary->StairRightD;
		Left_TypeConnections = ArrayDictionary->StairRightL;
		Right_TypeConnections = ArrayDictionary->StairRightR;
		
		break;
		
	case ETileType::Void:
		Up_TypeConnections = ArrayDictionary->VoidU;
		Down_TypeConnections = ArrayDictionary->VoidD;
		Left_TypeConnections = ArrayDictionary->VoidL;
		Right_TypeConnections = ArrayDictionary->VoidR;
		break;

	default:
		return;
	}
}

void ATileBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(PlayerHasEnteredTile)
	{
		return;
	}
	
	APlayerCharacter* PlayerRef = Cast<APlayerCharacter>(OtherActor);
	
	if(PlayerRef)
	{
		PlayerHasEnteredTile = true;
			
		//Overlapped actor is character... Execute overlap code:

		GameMode->RegisterTileExploration(XPos, YPos, EExplorationState::Explored);
		GameMode->ResetTempStats();

		if(!EnemySpawners.IsEmpty() && WallsUp == false)
		{
			int NumberOfEnemiesToSpawn = GetNumberOfEnemiesToSpawn();
			if(NumberOfEnemiesToSpawn > EnemySpawners.Num())
			{
				NumberOfEnemiesToSpawn = EnemySpawners.Num();
			}
			
			for (auto Index{0}; Index < NumberOfEnemiesToSpawn; Index++)
			{
				AEnemySpawner* tempSpawner = Cast<AEnemySpawner>(EnemySpawners[Index]);
				
				ABaseEnemy* NewEnemy = GetWorld()->SpawnActor<ABaseEnemy>(tempSpawner->GetRandomEnemyClass(), EnemySpawners[Index]->GetActorLocation(), FRotator(0, 0, 0));
				NewEnemy->OwningTile = this;
			}

			WallsUp = true;

			if(TileEnemyInfoComponent->CanTrapUntilEnemiesKilled)
			{
				int WallSpawnHeight = -2000;
				if(ThisTileType==ETileType::LevelTwo)
				{
					WallSpawnHeight= -1600;
				}
				
				UpWall = GetWorld()->SpawnActor<AActor>(FightWallClass, FVector(GetActorLocation().X+1100, GetActorLocation().Y ,WallSpawnHeight), FRotator(0, 0, 0));
				DownWall = GetWorld()->SpawnActor<AActor>(FightWallClass, FVector(GetActorLocation().X-1100, GetActorLocation().Y ,WallSpawnHeight), FRotator(0, 0, 0));
				LeftWall = GetWorld()->SpawnActor<AActor>(FightWallClass, FVector(GetActorLocation().X, GetActorLocation().Y+1100 ,WallSpawnHeight), FRotator(0, 90, 0));
				RightWall = GetWorld()->SpawnActor<AActor>(FightWallClass, FVector(GetActorLocation().X, GetActorLocation().Y-1100 ,WallSpawnHeight), FRotator(0, 90, 0));

				GameMode->OnWallsUp();
			}
			
			NumberOfAliveEnemies = NumberOfEnemiesToSpawn;
		}

		else if(EnemySpawners.IsEmpty())
		{
			GameMode->RegisterTileExploration(XPos, YPos, EExplorationState::Cleared);
			GameMode->ResetTempStats();

			SpawnLoot();
		}
	}
}

void ATileBase::SpawnLoot()
{
	for (auto Index{0}; Index<LootSpawners.Num(); Index++)
	{
		LootSpawners[Index]->SpawnLoot();
	}
}

int ATileBase::GetNumberOfEnemiesToSpawn()
{
	if(GameMode->CurrentDifficulty < 4)
	{
		return 1;
	}
	if(GameMode->CurrentDifficulty >= 4 && GameMode->CurrentDifficulty < 10)
	{
		return 2;
	}
	if(GameMode->CurrentDifficulty >= 10 && GameMode->CurrentDifficulty < 16)
	{
		return 3;
	}
	if(GameMode->CurrentDifficulty >= 16 && GameMode->CurrentDifficulty < 21)
	{
		return 4;
	}
	if(GameMode->CurrentDifficulty >= 21 && GameMode->CurrentDifficulty < 25)
	{
		return 5;
	}
	if(GameMode->CurrentDifficulty >= 25)
	{
		return 100;
	}
	return 100;
}

// Called every frame
void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

