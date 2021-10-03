// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTown.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "MyGameInstance.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformMath.h"

FVector ABaseTown::Ray(FVector2D ScreenPosition)
{
	FVector WorldPosition;
	FVector WorldDirection;
	APlayerController* PlayerController1 = UGameplayStatics::GetPlayerController(this, 0);
	UGameplayStatics::DeprojectScreenToWorld(PlayerController1, ScreenPosition, WorldPosition, WorldDirection);
	while (WorldPosition.Z > 120)
	{
		WorldPosition += WorldDirection*5;
	}
	return WorldPosition;
}

bool ABaseTown::IsPlaceTaken(int x, int y)
{
	for (int i = 1; i < FlyBuilding->Grid.X+1; i++)
	{
		for (int j = 0; j < FlyBuilding->Grid.Y; j++)
		{
			if(Grid[(x + i - 1) * i + y + j] != nullptr)
				return true;
		}
	}
	return false;
}

// Sets default values
ABaseTown::ABaseTown()
	:
	GridSize(FVector2D(15,10))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(GetRootComponent());

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);

	InputComponent = CreateDefaultSubobject<UInputComponent>("Input Component");
	SetupPlayerInputComponent(InputComponent);

}

// Called when the game starts or when spawned
void ABaseTown::BeginPlay()
{
	Super::BeginPlay();

	Grid.SetNum(GridSize.X * GridSize.Y);
	
	EnableInput(UGameplayStatics::GetPlayerController(this,0));
}

void ABaseTown::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

	InputComponent->BindTouch(IE_Pressed, this, &ABaseTown::OnTouchPress);
	InputComponent->BindTouch(IE_Repeat, this, &ABaseTown::OnTouchMove);



}

void ABaseTown::StartPlacingBuilding()
{
	if (FlyBuilding)
	{
		FlyBuilding->Destroy();
	}

	UE_LOG(LogTemp, Log, TEXT("IsPressed"));

	FActorSpawnParameters SpawnParametrs;
	FlyBuilding = GetWorld()->SpawnActor<ABuilding>(BuildingClass, GetActorLocation(), FRotator(0,0,0), SpawnParametrs);
}

void ABaseTown::PlaceBuilding(FVector Location)
{
	FVector WorldPosition = Ray(FVector2D(Location.X, Location.Y));

	WorldPosition.X = FMath::Clamp(WorldPosition.X, EdgeInforamation.LeftUp.X , EdgeInforamation.RightUp.X );
	WorldPosition.Y = FMath::Clamp(WorldPosition.Y, EdgeInforamation.LeftUp.Y , EdgeInforamation.LeftDown.Y );

	int x = ((int)WorldPosition.X + (int)EdgeInforamation.RightDown.X) / ((int)EdgeInforamation.RightDown.X*2 / (int)GridSize.X);
	int y = ((int)WorldPosition.Y + (int)EdgeInforamation.RightDown.Y) / ((int)EdgeInforamation.RightDown.Y*2 / (int)GridSize.Y);

	if (IsPlaceTaken(x, y))
	{
		return;
	}

	for (int i = 1; i < (int)FlyBuilding->Grid.X+1; i++)
	{
		for (int j = 0; j < (int)FlyBuilding->Grid.Y; j++)
		{
			Grid[(x + i - 1)*i + y + j] = FlyBuilding;
			UE_LOG(LogTemp, Log, TEXT("%d"),j);
		}
	}

	
	UE_LOG(LogTemp, Log, TEXT("Postavil"));
	FlyBuilding = nullptr;
	
}


void ABaseTown::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	StartPlacingBuilding();
}

void ABaseTown::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	FVector2D ScreenPosition;

	APlayerController* PlayerController1 = UGameplayStatics::GetPlayerController(this, 0);

	ScreenPosition = FVector2D(Location.X, Location.Y);

	FVector NewLocation = Ray(ScreenPosition);

	NewLocation.X = FMath::Clamp(NewLocation.X, EdgeInforamation.LeftUp.X , EdgeInforamation.RightUp.X );
	NewLocation.Y = FMath::Clamp(NewLocation.Y, EdgeInforamation.LeftUp.Y, EdgeInforamation.LeftDown.Y );
	
	int multiplierX = EdgeInforamation.LeftUp.X - EdgeInforamation.RightUp.X;
	NewLocation.X = (FMath::CeilToInt(NewLocation.X) / (int)(multiplierX / GridSize.X) ) * (multiplierX / GridSize.X);

	int multiplierY = EdgeInforamation.LeftUp.Y - EdgeInforamation.LeftDown.Y;
	NewLocation.Y = (FMath::CeilToInt(NewLocation.Y) / (int)(multiplierY / GridSize.Y)) * (multiplierY / GridSize.Y);

	FlyBuilding->SetActorLocation(NewLocation);


}

// Called every frame
void ABaseTown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

