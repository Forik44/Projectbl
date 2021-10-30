#include "EndGameActor.h"

AEndGameActor::AEndGameActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AEndGameActor::AddEnemyToEnd);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AEndGameActor::DeleteInEnd);
}

void AEndGameActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEndGameActor::GetDamage()
{
	for (auto Enemy : EnemiesInEnd)
	{
		HealthComponent->AddHealth(-Enemy->Damage);
	}
}

void AEndGameActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndGameActor::AddEnemyToEnd(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Add to End"));
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (!Enemy)
	{
		return;
	}
	EnemiesInEnd.Add(Enemy);

	if (EnemiesInEnd.Num() == 1)
	{
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AEndGameActor::GetDamage, Enemy->ImpactSpeed, true);
	}
}

void AEndGameActor::DeleteInEnd(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("Delete In End"));
	for (auto Enemy : EnemiesInEnd) {
		AActor* OurActor = Cast<AActor>(Enemy);
		if (OurActor == OtherActor)
		{
			if (EnemiesInEnd.Num() == 1)
			{
				GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
			}
			EnemiesInEnd.Remove(Enemy);
			break;
		}
	}
}

