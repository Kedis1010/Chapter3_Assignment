#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"

AMineItem::AMineItem()
{
	ExplosionDelay = 5.0f;
	ExplosionDamage = 30.0f;
	ExplosionRadius = 300.0f;
	ItemType = "Mine";
	
	ExplosionRadiusComp = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionRadius"));
	ExplosionRadiusComp->InitSphereRadius(ExplosionRadius);						// Sphere Component 내장 함수. 해당 구(Sphere)의 반경을 절대값으로 설정할 수 있다,
	ExplosionRadiusComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));	// SetCollisionProfileName으로 해당 Collision이 어떻게 작동할지 설정해주기.
	ExplosionRadiusComp->SetupAttachment(Scene);
}

void AMineItem::ActivateItem(AActor* Activator)
{
	GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this, &AMineItem::Explode, ExplosionDelay, false);
	// World에서 TimerManager을 가져온 뒤, SetTimer 호출.
	// 여기서 인수는 차례대로 
	// ExplosionTimerHandle(사용할 시계 핸들),
	// this(시계를 사용할 객체, 지금은 이 객체),
	//  &AMineItem::Explode(타이머 완료 시 호출할 함수),
	// ExplosionDelay(설정할 타이머 시간),
	// false (타이머가 반복할것인지)
}

void AMineItem::Explode()
{
	TArray<AActor*> OverlappingActors;
	ExplosionRadiusComp->GetOverlappingActors(OverlappingActors);
	//GetOverlappingActors는 호출된 그 순간에 오버랩(충돌)된 객체들 전부를 가져오는 함수다. 이 객체들을 TArray<AActor*>로 저장해주는 것.

	for (AActor* Actor : OverlappingActors)	//TArray에 있는 AActor을 순환
	{
		if (Actor && Actor->ActorHasTag("Player"))	//만약 이 액터가 플레이어라면?
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Player taken damaged %d by Mine"), ExplosionDamage));	//데미지를 준다.
		}
	}
	DestroyItem();	//반복문 끝난 뒤 부수기
}
