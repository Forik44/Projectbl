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
	while (WorldPosition.Z > 0)
	{
		WorldPosition += WorldDirection*5;
	}
	return WorldPosition;
}

// Sets default values
ABaseTown::ABaseTown()
	:
	GridSize(FVector2D(100,100))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(GetRootComponent());

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->AddLocalOffset(FVector(0, 0, 300));

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
	
	UE_LOG(LogTemp, Log, TEXT("IsMoved"));

	
	NewLocation.X = (FMath::RoundToInt(NewLocation.X) / (int)GridSize.X) * GridSize.X;

	NewLocation.Y = (FMath::RoundToInt(NewLocation.Y) / (int)GridSize.Y) * GridSize.Y;

	FlyBuilding->SetActorLocation(NewLocation);


}

// Called every frame
void ABaseTown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

