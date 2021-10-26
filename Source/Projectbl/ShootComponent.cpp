#include "ShootComponent.h"
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


}

void UShootComponent::SpawnProjectile()
{
	if (ShootInfo.ShootedEnemies.Num() == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(ShootTimer);
		return;
	}
	FActorSpawnParameters SpawnParametrs;
	AProjectile* Projectile;
	Projectile = GetWorld()->SpawnActor<AProjectile>(ShootInfo.ProjectileClass, GetOwner()->GetActorTransform(), SpawnParametrs);
	if (Projectile)
	{
		Projectile->Enemy = ShootInfo.ShootedEnemies[0];
	}
	Projectile->SubscribeEvent();
}

void UShootComponent::StartShooting()
{
	ABuilding* OurBuilding = Cast<ABuilding>(this->GetOwner());
	if (ShootInfo.ShootedEnemies.Num() == 1 && !OurBuilding->IsFly)
	{
		GetWorld()->GetTimerManager().SetTimer(ShootTimer, this, &UShootComponent::SpawnProjectile, ShootInfo.ShootRate, true);
	}
	
}


