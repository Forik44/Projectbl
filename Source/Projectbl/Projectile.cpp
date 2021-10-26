#include "Projectile.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::FoundEnemy);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Enemy) {
		return;
	}
	FRotator ProjectileRotation = this->GetActorRotation();
	FVector ProjectileLocation = this->GetActorLocation();
	
	FVector EnemyLocation = Enemy->GetActorLocation();
	
	
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(ProjectileLocation, EnemyLocation+FVector(0,0,40));
	FRotator NormalRotation = UKismetMathLibrary::NormalizedDeltaRotator(Rotation, ProjectileRotation);

	/*NormalRotation = FMath::Clamp(NormalRotation, -2.f, 2.f);*/

	
	this->AddActorLocalRotation(NormalRotation);

}

void AProjectile::FoundEnemy(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	this->Destroy();
}

