#include "ShootComponent.h"
#include "Building.h"

UShootComponent::UShootComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

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
	SpawnParametrs.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AProjectile* Projectile;
	Projectile = GetWorld()->SpawnActor<AProjectile>(ShootInfo.ProjectileClass, GetOwner()->GetActorLocation() + FVector(0,0,200), GetOwner()->GetActorRotation(),  SpawnParametrs);
	if (Projectile)
	{
		Projectile->Enemy = ShootInfo.ShootedEnemies[0];
	}
	Projectile->SubscribeEvent();
}

void UShootComponent::StartShooting()
{
	ABuilding* OurBuilding = Cast<ABuilding>(this->GetOwner());
	UE_LOG(LogTemp, Log, TEXT("Function"));
	if (ShootInfo.ShootedEnemies.Num() >= 1 && !OurBuilding->IsFly)
	{
		UE_LOG(LogTemp, Log, TEXT("shoot"));
		GetWorld()->GetTimerManager().SetTimer(ShootTimer, this, &UShootComponent::SpawnProjectile, ShootInfo.ShootRate, true);
	}
	
}


