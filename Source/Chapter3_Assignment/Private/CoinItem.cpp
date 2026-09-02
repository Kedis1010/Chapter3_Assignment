// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"
#include "KedisGameState.h"
ACoinItem::ACoinItem()
{
	PointValue = 0;
	ItemType = "DefaultCoin";
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (UWorld* World = GetWorld())
		{
			if (AKedisGameState* GameState = World->GetGameState<AKedisGameState>())
			{
				GameState->AddScore(PointValue);

				GameState->OnCoinCollected();
			}
		}

		DestroyItem();
	}
}
