// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class PROJECTBL_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	int Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FVector2D Grid;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
