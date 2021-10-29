#include "EnemySpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"

AEnemySpawner::AEnemySpawner()
	:
	CurrentSpawnStage(0),
	SpawnedEnemies(0)
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	

	StartSpawnEnemies();
}

void AEnemySpawner::StartSpawnStage()
{
	FActorSpawnParameters SpawnParametrs;
	if (SpawnedEnemies == EnemyInfo.SpawnStages[CurrentSpawnStage].NumberOfEnemies)
	{
		SpawnedEnemies = 0;
		CurrentSpawnStage++;
		GetWorld()->GetTimerManager().SetTimer(ChangeStageTimer, this, &AEnemySpawner::StartSpawnEnemies, EnemyInfo.CoolDownSpawnStages, false);
	}
	else
	{
		SpawnedEnemies++;
		GetWorld()->SpawnActor<AEnemy>(EnemyInfo.SpawnStages[CurrentSpawnStage].EnemyClass, GetActorTransform(), SpawnParametrs);
		GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &AEnemySpawner::StartSpawnStage, EnemyInfo.SpawnStages[CurrentSpawnStage].CoolDownSpawnEnemies, false);
	}
}

void AEnemySpawner::StartSpawnEnemies()
{
	if (CurrentSpawnStage > EnemyInfo.SpawnStages.Num() - 1)
	{
		return;
	}
	StartSpawnStage();
	
	
	
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

