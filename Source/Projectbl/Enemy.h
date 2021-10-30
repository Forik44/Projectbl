#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SplineComponent.h"
#include "HealthComponent.h"
#include "Enemy.generated.h"

UCLASS()
class PROJECTBL_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

	 

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	UHealthComponent*  HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Economic")
	int Award;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Economic")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Economic")
	float ImpactSpeed;
	
};
