// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"


UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> GameStoreWidget(TEXT("/Game/UI/Menues/GameStore"));
	if (!ensure(GameStoreWidget.Class != nullptr)) return;

	GameStoreWidgetClass = GameStoreWidget.Class;
}

void UMyGameInstance::ShowWidget()
{
	UUserWidget* GameStore = CreateWidget<UUserWidget>(this, GameStoreWidgetClass);
	GameStore->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(GameStore->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
}
