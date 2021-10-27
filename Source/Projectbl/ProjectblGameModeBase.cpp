// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectblGameModeBase.h"

int AProjectblGameModeBase::GetMoney()
{
	return Money;
}

void AProjectblGameModeBase::AddMoney(int money)
{
	Money += money;
}
