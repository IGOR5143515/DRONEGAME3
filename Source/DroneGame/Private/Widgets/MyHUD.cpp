


#include "Widgets/MyHUD.h"
#include "Blueprint/UserWidget.h"

void AMyHUD::BeginPlay()
{

	Super::BeginPlay();

	auto PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass);
	if (PlayerWidget) {
		PlayerWidget->AddToViewport();
	}

}
