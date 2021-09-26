// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTown.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "MyGameInstance.h"

// Sets default values
ABaseTown::ABaseTown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(GetRootComponent());

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void ABaseTown::BeginPlay()
{
	Super::BeginPlay();
	
	Collision->OnInputTouchBegin.AddDynamic(this, &ABaseTown::OpenStoreMenu);
}

void ABaseTown::OpenStoreMenu(ETouchIndex::Type Type, UPrimitiveComponent* ActorTouched)
{
	UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance)
		return;
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
	if (!MyGameInstance)
		return;
	MyGameInstance->ShowWidget();
	UE_LOG(LogTemp, Log, TEXT("IsPressed"));
}

// Called every frame
void ABaseTown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

