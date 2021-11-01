#include "Building.h"


ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	IsFly = true;
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}



