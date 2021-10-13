// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"

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
	SpawnProjectile(nullptr);
	// ...
	
}


// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//if (i % 1000 == 0) {
		SpawnProjectile(nullptr);
	//	i++;
	//}
	// ...
}

void UShootComponent::SpawnProjectile(AEnemy* Enemy)
{
	FActorSpawnParameters SpawnParametrs;
	AProjectile* Projectile;
	Projectile = GetWorld()->SpawnActor<AProjectile>(ShootInfo.ProjectileClass, GetOwner() ->GetActorTransform(), SpawnParametrs);
	//Projectile->Enemy = Enemy;
}

