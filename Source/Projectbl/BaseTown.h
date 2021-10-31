// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Building.h"
#include "BaseTown.generated.h"

USTRUCT(BlueprintType)
struct FEdgeInforamation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FVector LeftUp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FVector RightUp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FVector RightDown;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FVector LeftDown;
};

UCLASS()
class PROJECTBL_API ABaseTown : public AActor
{
	GENERATED_BODY()
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FVector2D GridSize;

	TArray<ABuilding*> Grid;



private:

	FVector Ray(FVector2D ScreenPosition);
		
	bool IsPlaceTaken(int x, int y);
	bool CanBePlaced, IsPlacing;

	FVector CurrentLocation;
	
public:	
	
	ABaseTown();

	virtual void Tick(float DeltaTime) override;

	UInputComponent* InputComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	ABuilding* FlyBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base")
	UBoxComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FEdgeInforamation EdgeInforamation;

	UFUNCTION(BlueprintCallable, Category = "Building")
	void StartPlacingBuilding(TSubclassOf<ABuilding> BuildingClass);

	UFUNCTION(BlueprintCallable, Category = "Building")
	void PlaceBuilding(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Building")
	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);

	
};
