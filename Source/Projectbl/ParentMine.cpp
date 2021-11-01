// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentMine.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

void AParentMine::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(CreateMoneyTimer, this, &AParentMine::CreateMoney, Efficincy, true);
}

void AParentMine::CreateMoney()
{
	AProjectblGameModeBase* GameMode = Cast<AProjectblGameModeBase>(UGameplayStatics::GetGameMode(this));

	GameMode->AddMoney(Power);

}
