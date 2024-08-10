

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"


UCLASS()
class DRONEGAME_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	

	virtual void BeginPlay()override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>PlayerWidgetClass;

};
