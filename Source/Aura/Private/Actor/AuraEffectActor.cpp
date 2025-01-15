// Copyright Pascal Lefev


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(FName("SceneRoot")));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass)
{
	const auto TargetAbilitySystemComponent{ UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor) };
	if (!TargetAbilitySystemComponent) return;

	auto GameplayEffectContext{ TargetAbilitySystemComponent->MakeEffectContext() };
	GameplayEffectContext.AddSourceObject(this);
	if (InstantGameplayEffectClass)
	{
		const auto GameplayEffectSpec{ TargetAbilitySystemComponent->MakeOutgoingSpec(
			InstantGameplayEffectClass,
			1.f,
			GameplayEffectContext)
		};
		TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpec.Data.Get());
	}
	
	if (DurationGameplayEffectClass)
	{
		const auto GameplayEffectSpec{ TargetAbilitySystemComponent->MakeOutgoingSpec(
			DurationGameplayEffectClass,
			1.f,
			GameplayEffectContext)
		};
		TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpec.Data.Get());
	}
}
