// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "ParentTower.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBL_API AParentTower : public ABuilding
{
	GENERATED_BODY()

public:
	AParentTower();

protected:
	virtual void BeginPlay() override;
public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
	UShootComponent* ShootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
	USphereComponent* Collision;

	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void AddEnemy(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void DeleteEnemy(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void HideCollision();

};
