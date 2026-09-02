// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "PlayerCharacter.h"
#include "MainPlayerController.h"
#include "KedisGameState.h"

AMainGameMode::AMainGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
	GameStateClass = AKedisGameState::StaticClass();
}