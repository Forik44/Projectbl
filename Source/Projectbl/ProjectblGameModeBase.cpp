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

void AProjectblGameModeBase::AddMoney(int money)
{
	Money += money;
}

