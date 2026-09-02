// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingPotion.h"
#include "PlayerCharacter.h"

AHealingPotion::AHealingPotion()
{
	HealAmount = 20;
	ItemType = "HealingPotion";
}

void AHealingPotion::ActivateItem(AActor* Activator)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Activator))
	{
		PlayerCharacter->AddHealth(HealAmount);
	}
	DestroyItem();
}