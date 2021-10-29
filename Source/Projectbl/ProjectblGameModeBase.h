#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Building.h"
#include "ParentTower.h"
#include "ProjectblGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

USTRUCT(BlueprintType)
struct FTowersInfo
{

	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildings")
	TArray<TSubclassOf<AParentTower>> TowerClasses;

};

USTRUCT(BlueprintType)
struct FMinesInfo 
{

	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildings")
		TArray<TSubclassOf<AParentTower>> TowerClasses;

};

USTRUCT(BlueprintType)
struct FBuildingsInfo
{

	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildings")
	TArray<FTowersInfo> TowerInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildings")
	TArray<FMinesInfo> BuildingsInfo;

};

UCLASS()
class PROJECTBL_API AProjectblGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Economic")
	void AddMoney(int money);

	UFUNCTION(BlueprintCallable, Category = "Economic")
	int GetMoney();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();

	bool IsGameOver;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOver;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buildings")
	FBuildingsInfo BuildingsInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Economic")
	int Money;
};
