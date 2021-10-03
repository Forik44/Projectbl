// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Building.h"
#include "BaseTown.generated.h"

UCLASS()
class PROJECTBL_API ABaseTown : public AActor
{
	GENERATED_BODY()
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FVector2D GridSize;

	TArray<ABuilding*> Grid;

	UFUNCTION(BlueprintCallable, Category = "Building")
	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);
	UFUNCTION(BlueprintCallable, Category = "Building")
	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);


private:

	FVector Ray(FVector2D ScreenPosition);
		
	
public:	
	
	ABaseTown();

	virtual void Tick(float DeltaTime) override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	UInputComponent* InputComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	ABuilding* FlyBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base")
	UBoxComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	TSubclassOf<ABuilding> BuildingClass;

	UFUNCTION(BlueprintCallable, Category = "Building")
	void StartPlacingBuilding();

	

	
};
