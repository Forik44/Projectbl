// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTown.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "MyGameInstance.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GenericPlatform/GenericPlatformMath.h"

FVector ABaseTown::Ray(FVector2D ScreenPosition)
{
	FVector WorldPosition;
	FVector WorldDirection;
	APlayerController* PlayerController1 = UGameplayStatics::GetPlayerController(this, 0);
	UGameplayStatics::DeprojectScreenToWorld(PlayerController1, ScreenPosition, WorldPosition, WorldDirection);
	FVector StartPosition = WorldPosition;

	FHitResult OutHit;
	FCollisionObjectQueryParams ObjectQueryParams;
	FCollisionQueryParams Params;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	bool isObject = GetWorld()->LineTraceSingleByObjectType(OutHit, StartPosition + WorldDirection * 25, WorldPosition + WorldDirection * 5000, ObjectQueryParams, Params);
	WorldPosition = OutHit.Location;
	if (!OutHit.GetActor())
	{
		CanBePlaced = false;
		return WorldPosition;
	}
	if(UKismetMathLibrary::ClassIsChildOf(OutHit.GetActor()->GetClass(), ABaseTown::StaticClass()))
	{
		CanBePlaced = true;
	}
	else
	{
		CanBePlaced = false;
	}
	return WorldPosition;
}

bool ABaseTown::IsPlaceTaken(int x, int y)
{
	for (int i = 0; i < FlyBuilding->Grid.X; i++)
	{
		for (int j = 0; j < FlyBuilding->Grid.Y; j++)
		{
			if(Grid[(x + i) * (int)GridSize.Y + y + j] != nullptr)
				return true;
		}
	}
	return false;
}

// Sets default values
ABaseTown::ABaseTown()
	:
	GridSize(FVector2D(5,5))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(GetRootComponent());

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);

	InputComponent = CreateDefaultSubobject<UInputComponent>("Input Component");

}

// Called when the game starts or when spawned
void ABaseTown::BeginPlay()
{
	Super::BeginPlay();

	Grid.SetNum(GridSize.X * GridSize.Y);
	
	EnableInput(UGameplayStatics::GetPlayerController(this,0));
}


void ABaseTown::StartPlacingBuilding(TSubclassOf<ABuilding> BuildingClass)
{
	if (FlyBuilding)
	{
		FlyBuilding->Destroy();
	}
	IsPlacing = true;
	FActorSpawnParameters SpawnParametrs;
	FlyBuilding = GetWorld()->SpawnActor<ABuilding>(BuildingClass, FVector(0,0,0), FRotator(0,0,0), SpawnParametrs);

}

void ABaseTown::PlaceBuilding(FVector Location)
{
	FVector WorldPosition = Ray(FVector2D(Location.X, Location.Y));
	if (IsPlacing)
	{
		int multiplierX = EdgeInforamation.LeftUp.X - EdgeInforamation.RightUp.X;
		WorldPosition.X = ((FMath::CeilToInt(WorldPosition.X) / (int)(multiplierX / GridSize.X)) * (multiplierX / GridSize.X));

		int multiplierY = EdgeInforamation.LeftUp.Y - EdgeInforamation.LeftDown.Y;
		WorldPosition.Y = ((FMath::CeilToInt(WorldPosition.Y) / (int)(multiplierY / GridSize.Y)) * (multiplierY / GridSize.Y));

		WorldPosition.X = FMath::Clamp(WorldPosition.X, EdgeInforamation.LeftUp.X, EdgeInforamation.RightUp.X);
		WorldPosition.Y = FMath::Clamp(WorldPosition.Y, EdgeInforamation.LeftUp.Y, EdgeInforamation.LeftDown.Y);

		int x = ((int)WorldPosition.X + (int)EdgeInforamation.RightDown.X) / ((int)EdgeInforamation.RightDown.X * 2 / (int)GridSize.X);
		int y = ((int)WorldPosition.Y + (int)EdgeInforamation.RightDown.Y) / ((int)EdgeInforamation.RightDown.Y * 2 / (int)GridSize.Y);

		if (IsPlaceTaken(x, y))
		{
			return;
		}

		for (int i = 0; i < (int)FlyBuilding->Grid.X; i++)
		{
			for (int j = 0; j < (int)FlyBuilding->Grid.Y; j++)
			{
				Grid[(x + i) * (int)GridSize.Y + y + j] = FlyBuilding;
			}
		}
		FlyBuilding->HideCollision();
		FlyBuilding = nullptr;
		IsPlacing = false;
	}
}


void ABaseTown::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{

	FVector2D ScreenPosition;

	APlayerController* PlayerController1 = UGameplayStatics::GetPlayerController(this, 0);

	ScreenPosition = FVector2D(Location.X, Location.Y);
	FVector NewLocation = Ray(ScreenPosition);
	if (IsPlacing && CanBePlaced)
	{

	
		NewLocation.X = FMath::Clamp(NewLocation.X, EdgeInforamation.LeftUp.X, EdgeInforamation.RightUp.X);
		NewLocation.Y = FMath::Clamp(NewLocation.Y, EdgeInforamation.LeftUp.Y, EdgeInforamation.LeftDown.Y);

		int multiplierX = EdgeInforamation.LeftUp.X - EdgeInforamation.RightUp.X;
		NewLocation.X = ((FMath::CeilToInt(NewLocation.X) / (int)(multiplierX / GridSize.X)) * (multiplierX / GridSize.X));

		int multiplierY = EdgeInforamation.LeftUp.Y - EdgeInforamation.LeftDown.Y;
		NewLocation.Y = ((FMath::CeilToInt(NewLocation.Y) / (int)(multiplierY / GridSize.Y)) * (multiplierY / GridSize.Y));

		UGameplayStatics::ProjectWorldToScreen(PlayerController1, NewLocation, ScreenPosition);
		Ray(ScreenPosition);
		if(CanBePlaced)
		FlyBuilding->SetActorLocation(NewLocation);
	}
}

// Called every frame
void ABaseTown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

