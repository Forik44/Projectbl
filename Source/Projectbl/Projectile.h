// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "Projectile.generated.h"

UCLASS()
class PROJECTBL_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Destroy")
	void DestroyProjectile();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
    AEnemy* Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
	USphereComponent* Collision;

	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void FoundEnemy(UPrimitiveComponent* OurComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void SubscribeEvent();


};
