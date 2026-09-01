// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealingPotion.generated.h"

UCLASS()
class CHAPTER3_ASSIGNMENT_API AHealingPotion : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AHealingPotion();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float HealAmount;

	virtual void ActivateItem(AActor* Activator) override;
};
