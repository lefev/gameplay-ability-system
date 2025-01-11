// Copyright Pascal Lefev


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto Widget{ CreateWidget(GetWorld(), OverlayWidgetClass) };
	Widget->AddToViewport();
	
}
