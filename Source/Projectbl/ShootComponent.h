// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enemy.h"
#include "Projectile.h"
#include "ShootComponent.generated.h"

USTRUCT(BlueprintType)
struct FShootInfo
{

	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		TArray<AEnemy*> ShootedEnymed ;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float ShootRate;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBL_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	int i;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
	float radius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
	FShootInfo ShootInfo;

	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void SpawnProjectile(AEnemy* Enemy);

		
};
