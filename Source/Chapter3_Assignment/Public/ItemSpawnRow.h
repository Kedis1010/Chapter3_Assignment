#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnRow.generated.h"

USTRUCT(BlueprintType)
struct FItemSpawnRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;
	// TSubclassOf 는 하드 레퍼런스, 클래스가 항상 메모리에 로드된 상태에서 바로 접근
	// TSoftclassPtr 는 소프트 레퍼런스, 클래스의 경로만 유지해두는 것. 여러가지 다른 조치도 필요하다. 공부 필요

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Spawnchance;
};
