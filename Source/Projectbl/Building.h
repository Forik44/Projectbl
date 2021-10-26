// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootComponent.h"
#include "Components/SphereComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
	UShootComponent* ShootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
	USphereComponent* Collision;

	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void AddEnemy(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void DeleteEnemy(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void HideCollision();

	bool IsFly;
};
