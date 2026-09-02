// Fill out your copyright notice in the Description page of Project Settings.


#include "KedisGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "CoinItem.h"

#include "MainGameInstance.h"

AKedisGameState::AKedisGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 30.0f;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
}

void AKedisGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();
}

int32 AKedisGameState::GetScore()const
{
	return Score;
}

void AKedisGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMainGameInstance* MainGameInstance = Cast<UMainGameInstance>(GameInstance);
		if (MainGameInstance)
		{
			MainGameInstance->AddToScore(Amount);
		}
	}
}

void AKedisGameState::StartLevel()
{

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMainGameInstance* MainGameInstance = Cast<UMainGameInstance>(GameInstance);
		if (MainGameInstance)
		{
			CurrentLevelIndex = MainGameInstance->CurrentLevelIndex;
		}
	}
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 40;

	for (int32 i = 0; i < ItemToSpawn; i++)
	{
		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}

	GetWorldTimerManager().SetTimer(LevelTimerHandle, this, &AKedisGameState::OnLevelTimeUp, LevelDuration, false);
	UE_LOG(LogTemp, Warning, TEXT("Level %d Start, Spawned %d coin"), CurrentLevelIndex + 1, SpawnedCoinCount);
}

void AKedisGameState::OnLevelTimeUp()
{
	EndLevel();
}

void AKedisGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMainGameInstance* MainGameInstance = Cast<UMainGameInstance>(GameInstance);
		if (MainGameInstance)
		{
			AddScore(Score);
			CurrentLevelIndex++;
			MainGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}

void AKedisGameState::OnCoinCollected()
{
	CollectedCoinCount++;
	UE_LOG(LogTemp, Warning, TEXT("Coin Collected : %d / %d"), CollectedCoinCount, SpawnedCoinCount);
	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		EndLevel();
	}
}

void AKedisGameState::OnGameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over"));
}