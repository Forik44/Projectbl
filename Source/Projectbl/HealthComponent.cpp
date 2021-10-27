#include "HealthComponent.h"
#include "ProjectblGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"


UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::AddHealth(int fix)
{
	Health += fix;
	if (Health <= 0)
	{
		AProjectblGameModeBase* GameMode = Cast<AProjectblGameModeBase>(UGameplayStatics::GetGameMode(this));
		AEnemy* Enemy = Cast<AEnemy>(GetOwner());
		GameMode->AddMoney(Enemy->Award);
		GetOwner()->Destroy();
		OnHealthEnded.Broadcast();
	}
}

