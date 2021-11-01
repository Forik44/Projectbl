#include "Building.h"


ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABuilding::AddEnemy);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABuilding::DeleteEnemy);
	IsFly = true;
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Collision->SetWorldLocation(Mesh->GetRelativeLocation());
}

void ABuilding::AddEnemy(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void ABuilding::HideCollision()
{
	Collision->SetHiddenInGame(true);
	IsFly = false;
	ShootComponent->StartShooting();
}

void ABuilding::DeleteEnemy(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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