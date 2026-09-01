#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

class CHAPTER3_ASSIGNMENT_API IItemInterface
{
	GENERATED_BODY()

	
public:
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) = 0;
	virtual void ActivateItem(AActor* Activator) = 0;
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	) = 0;
	virtual FName GetItemType() const = 0;
	//FName을 쓰는 이유는 TIL에 적어두었다. FString을 쓰는 것보다 효율적.

	// 지뢰 아이템, 힐링 아이템, 코인 아이템
	// 힐링, 코인 - 오버랩시 즉시 발동
	// 지뢰 - 범위 내에 오버랩 시 5초 후 폭발 - 폭발 시점에서 오버랩 시 데미지
};
