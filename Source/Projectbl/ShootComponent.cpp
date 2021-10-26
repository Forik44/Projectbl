#include "ShootComponent.h"
#include "Building.h"
// Fill out your copyright notice in the Description page of Project Settings.


// Sets default values for this component's properties
UShootComponent::UShootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ABuilding* OurBuilding = Cast<ABuilding>(this->GetOwner());
	if (ShootInfo.ShootedEnemies.Num() > 0 && !OurBuilding->IsFly)
	{
		for (int j = 0; j < CountOfEnemies && j < ShootInfo.ShootedEnemies.Num(); j++)
		{
			SpawnProjectile(ShootInfo.ShootedEnemies[j]);
			UE_LOG(LogTemp, Log, TEXT("Spawn"));
		}
	}

}

void UShootComponent::SpawnProjectile(AEnemy* Enemy)
{
	FActorSpawnParameters SpawnParametrs;
	AProjectile* Projectile;
	Projectile = GetWorld()->SpawnActor<AProjectile>(ShootInfo.ProjectileClass, GetOwner()->GetActorTransform(), SpawnParametrs);
	if (Projectile)
	{
		Projectile->Enemy = Enemy;
	}
}


