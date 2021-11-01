// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "ProjectblGameModeBase.h"
#include "ParentMine.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBL_API AParentMine : public ABuilding
{
	GENERATED_BODY()
public:
	

protected:
	
	virtual void BeginPlay() override;

	FTimerHandle CreateMoneyTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	int Power;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Economic")
	float Efficincy;

	UFUNCTION(BlueprintCallable, Category = "Economic")
	void CreateMoney();

};
