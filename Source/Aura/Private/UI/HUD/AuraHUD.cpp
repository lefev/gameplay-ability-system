// Copyright Pascal Lefev


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (M_OverlayWidgetController == nullptr)
	{
		M_OverlayWidgetController = NewObject<UOverlayWidgetController>(this, M_OverlayWidgetControllerClass);
		M_OverlayWidgetController->SetWidgetControllerParams(Params);
	}
	return M_OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,
                           UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet)
{
	checkf(M_OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, fill out BP_AuraHUD"))
	checkf(M_OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, fill out BP_AuraHUD"))
	
	const auto Widget{ CreateWidget(GetWorld(), M_OverlayWidgetClass) };
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	
	const FWidgetControllerParams WidgetControllerParams{PlayerController, PlayerState, AbilitySystemComponent, AttributeSet};
	const auto WidgetController{ GetOverlayWidgetController(WidgetControllerParams) };
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}
