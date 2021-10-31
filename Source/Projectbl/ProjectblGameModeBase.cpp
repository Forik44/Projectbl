#include "ProjectblGameModeBase.h"
#include "Kismet/GameplayStatics.h"

int AProjectblGameModeBase::GetMoney()
{
	return Money;
}

void AProjectblGameModeBase::EndGame()
{
	IsGameOver = true;

	GameOver.Broadcast();

	SetPause(UGameplayStatics::GetPlayerController(this, 0));
}

void AProjectblGameModeBase::WinGame()
{
	IsGameOver = true;

	WinGameOver.Broadcast();

	SetPause(UGameplayStatics::GetPlayerController(this, 0));
}

void AProjectblGameModeBase::StartCheckWinGame()
{
	GetWorld()->GetTimerManager().SetTimer(CheckWinGameTimer, this, &AProjectblGameModeBase::CheckWin, CheckWinTime, true);
}

void AProjectblGameModeBase::CheckWin()
{
	TArray<AActor*> Enemies;
	TSubclassOf<AEnemy> EnemyClass;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), Enemies);
	if (Enemies.Num() == 0)
	{
		WinGame();
	}
}

void AProjectblGameModeBase::AddMoney(int money)
{
	Money += money;
}

