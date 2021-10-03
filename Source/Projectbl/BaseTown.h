// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Building.h"
#include "BaseTown.generated.h"

USTRUCT(BlueprintType)
struct FRowsGrid
{	
	
	GENERATED_BODY()
public:
	TArray<ABuilding> Rows;

};

UCLASS()
class PROJECTBL_API ABaseTown : public AActor
{
	GENERATED_BODY()
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FVector2D GridSize;

	//TArray<FRowsGrid> Grid;

private:

	ABuilding* FlyBuilding; 
	
	void StartPlacingBuilding();
		
	
public:	
	
	ABaseTown();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base")
	UBoxComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	TSubclassOf<ABuilding> BuildingClass;

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void OpenStoreMenu(ETouchIndex::Type Type, UPrimitiveComponent* ActorTouched);
};
