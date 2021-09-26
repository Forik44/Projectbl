// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BaseTown.generated.h"


UCLASS()
class PROJECTBL_API ABaseTown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base")
	UBoxComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base")
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void OpenStoreMenu(ETouchIndex::Type Type, UPrimitiveComponent* ActorTouched);
};
