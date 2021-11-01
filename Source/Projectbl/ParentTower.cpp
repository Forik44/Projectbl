#include "ParentTower.h"


AParentTower::AParentTower()
{
	PrimaryActorTick.bCanEverTick = true;

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AParentTower::AddEnemy);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AParentTower::DeleteEnemy);
}

void AParentTower::BeginPlay()
{
	Super::BeginPlay();

}

void AParentTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Collision->SetWorldLocation(Mesh->GetRelativeLocation());
}

void AParentTower::AddEnemy(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* OurPawn = Cast<APawn>(OtherActor);
	if (!OurPawn)
	{
		return;
	}
	AEnemy* OurEnemy = Cast<AEnemy>(OurPawn);
	if (!OurEnemy)
	{
		return;
	}
	ShootComponent->ShootInfo.ShootedEnemies.Add(OurEnemy);
	ShootComponent->StartShooting();
}

void AParentTower::HideCollision()
{
	Collision->SetHiddenInGame(true);
	IsFly = false;
	ShootComponent->StartShooting();
}

void AParentTower::DeleteEnemy(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (auto Enemy : ShootComponent->ShootInfo.ShootedEnemies) {
		AActor* OurActor = Cast<AActor>(Enemy);
		if (OurActor == OtherActor)
		{
			ShootComponent->ShootInfo.ShootedEnemies.Remove(Enemy);
			break;
		}
	}
}