#include "Projectile.h"
#include "Kismet/KismetMathLibrary.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::FoundEnemy);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::DestroyProjectile()
{
	this->Destroy();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator ProjectileRotation = this->GetActorRotation();
	FVector ProjectileLocation = this->GetActorLocation();
	
	FVector EnemyLocation = Enemy->GetActorLocation();
	
	
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(ProjectileLocation, EnemyLocation+FVector(0,0,40));
	FRotator NormalRotation = UKismetMathLibrary::NormalizedDeltaRotator(Rotation, ProjectileRotation);

	this->AddActorLocalRotation(NormalRotation);

}

void AProjectile::FoundEnemy(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	this->Destroy();

	AEnemy* OtherEnemy = Cast<AEnemy>(OtherActor);
	if (!OtherEnemy) {
		return;
	}
	
	OtherEnemy->HealthComponent->AddHealth(-Damage);

}

void AProjectile::SubscribeEvent()
{
	if (!Enemy) {
		return;
	}
	Enemy->HealthComponent->OnHealthEnded.AddDynamic(this, &AProjectile::DestroyProjectile);
}

