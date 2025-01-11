// Copyright Pascal Lefev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UAuraUserWidget;
struct FWidgetControllerParams;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UFUNCTION(BlueprintCallable)
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);	

	void InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,
		UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet);
	
private:	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> M_OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> M_OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> M_OverlayWidgetControllerClass;
};
