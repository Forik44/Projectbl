#include "HealthComponent.h"
#include "ProjectblGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"


UHealthComponent::UHealthComponent()
{
	

}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void UHealthComponent::AddHealth(int fix)
{
	Health += fix;
	if (Health <= 0)
	{
		AProjectblGameModeBase* GameMode = Cast<AProjectblGameModeBase>(UGameplayStatics::GetGameMode(this));
		AEnemy* Enemy = Cast<AEnemy>(GetOwner());
		if (Enemy)
		{
			GameMode->AddMoney(Enemy->Award);
			OnHealthEnded.Broadcast();
			GetOwner()->Destroy();
		}
		else
		{
			GameMode->EndGame();
		}
	}
}

