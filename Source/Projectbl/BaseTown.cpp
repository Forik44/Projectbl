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
#include "ProjectblGameModeBase.h"
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
			if (x - i < 0 || y - j < 0)
			{
				return true;
			}
			if (Grid[(x - i) * (int)GridSize.Y + y - j] != nullptr)
			{
				return true;
			}
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
	UE_LOG(LogTemp, Log, TEXT("Function"));
	if (IsPlacing)
	{
		AProjectblGameModeBase* GameMode = Cast<AProjectblGameModeBase>(UGameplayStatics::GetGameMode(this));
		if (FlyBuilding->Cost > GameMode->GetMoney())
		{
			return;
		}
		
		int x = ((int)CurrentLocation.X - (int)EdgeInforamation.LeftUp.X) / (((int)EdgeInforamation.RightDown.X - (int)EdgeInforamation.LeftUp.X) / (int)GridSize.X);
		int y = ((int)CurrentLocation.Y - (int)EdgeInforamation.LeftUp.Y) / (((int)EdgeInforamation.RightDown.Y - (int)EdgeInforamation.LeftUp.Y) / (int)GridSize.Y);
		UE_LOG(LogTemp, Log, TEXT("Ne zanato"));
		for (int i = 0; i < (int)FlyBuilding->Grid.X; i++)
		{
			for (int j = 0; j < (int)FlyBuilding->Grid.Y; j++)
			{
				if(x - i < 0 || y - j < 0)
				{
					return;
				}
				Grid[(x - i) * (int)GridSize.Y + y - j] = FlyBuilding;
			}
		}
		GameMode->AddMoney(-FlyBuilding->Cost);

		AParentTower* Tower = Cast<AParentTower>(FlyBuilding);
		if (Tower)
		{
			Tower->HideCollision();
		}
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

		if (!CanBePlaced)
		{
			return;
		}

		int x = (NewLocation.X - EdgeInforamation.LeftUp.X) / ((EdgeInforamation.RightDown.X - EdgeInforamation.LeftUp.X) / GridSize.X);
		int y = (NewLocation.Y - EdgeInforamation.LeftUp.Y) / ((EdgeInforamation.RightDown.Y - EdgeInforamation.LeftUp.Y) / GridSize.Y);
		if (IsPlaceTaken(x, y))
		{
			return;
		}
		for (int i = 0; i < (int)FlyBuilding->Grid.X; i++)
		{
			for (int j = 0; j < (int)FlyBuilding->Grid.Y; j++)
			{
				if (i != 0 || j != 0)
				{
					FVector NearLocation;
					FVector NearLocation2;
					NearLocation.X = ((EdgeInforamation.RightDown.X - EdgeInforamation.LeftUp.X) * (x - i)) / GridSize.X + EdgeInforamation.LeftUp.X;
					NearLocation.Y = ((EdgeInforamation.RightDown.Y - EdgeInforamation.LeftUp.Y) * (y + j)) / GridSize.Y + EdgeInforamation.LeftUp.Y;
					NearLocation.Z = NewLocation.Z;
					UGameplayStatics::ProjectWorldToScreen(PlayerController1, NearLocation, ScreenPosition);
					Ray(ScreenPosition);
					if (!CanBePlaced)
					{
						return;
					}
				
				}	
			}
		}
		UE_LOG(LogTemp, Log, TEXT("Ne zanato"), x, y);
		FlyBuilding->SetActorLocation(NewLocation);
		CurrentLocation = NewLocation;
		
	}
}

// Called every frame
void ABaseTown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

