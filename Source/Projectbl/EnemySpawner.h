#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Enemy.h"
#include "EnemySpawner.generated.h"

USTRUCT(BlueprintType)
struct FSpawnStage
{

	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemySpawner")
	TSubclassOf<AEnemy> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemySpawner")
	int NumberOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemySpawner")
	float CoolDownSpawnEnemies;
};

USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{

	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemySpawner")
	TArray<FSpawnStage> SpawnStages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemySpawner")
	float CoolDownSpawnStages;
};

UCLASS()
class PROJECTBL_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle ChangeStageTimer;
	FTimerHandle EnemySpawnTimer;

	void StartSpawnStage();
	void StartSpawnEnemies();

private:
	int CurrentSpawnStage;
	int SpawnedEnemies;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemySpawner")
	FEnemySpawnInfo EnemyInfo;
};
