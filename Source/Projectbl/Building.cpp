// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABuilding::AddEnemy);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABuilding::DeleteEnemy);
	IsFly = true;
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Collision->SetWorldLocation(Mesh->GetRelativeLocation());
}

void ABuilding::AddEnemy(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Add"));
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
	UE_LOG(LogTemp, Log, TEXT("Delete"));
	for (auto Enemy : ShootComponent->ShootInfo.ShootedEnemies) {
		AActor* OurActor = Cast<AActor>(Enemy);
		if (OurActor == OtherActor)
		{
				ShootComponent->ShootInfo.ShootedEnemies.Remove(Enemy);
				break;
		}
	}



}