// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
	:
	CurrentSpawnStage(0),
	SpawnedEnemies(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
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

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

