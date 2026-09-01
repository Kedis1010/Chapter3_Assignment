// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingPotion.h"

AHealingPotion::AHealingPotion()
{
	HealAmount = 20;
	ItemType = "HealingPotion";
}

void AHealingPotion::ActivateItem(AActor* Activator)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Health Gained %d hp"), HealAmount));
	DestroyItem();
}