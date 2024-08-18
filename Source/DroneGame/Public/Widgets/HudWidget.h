#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget.generated.h"


UCLASS()
class DRONEGAME_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent()const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetAmmo();

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetMaxBullets();
	
};
