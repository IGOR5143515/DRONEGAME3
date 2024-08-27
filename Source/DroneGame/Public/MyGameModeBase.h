// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class AMyAIController;

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
	int32 PlayersNum = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
	int32 RoundsNum = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
	int32 RoundTime = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FLinearColor DefaultTeamColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FLinearColor>TeamColors;

};

UCLASS()
class DRONEGAME_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	public:
		AMyGameModeBase();
		virtual void StartPlay()override;

		virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController)override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	TSubclassOf<AMyAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FGameData GameData;

private:
	void SpawnBots();
	void StartRound();
	void GameTimerUpdate();
	void ResetPlayers();
	void ResetOnePlayer(AController * Controller);
	void CreateTeamsInfo();
	void SetPlayerColor(AController* Controller);
	FLinearColor DetermineColorByTeamID( int32 TeamID);



	int32 CurrentRound;
	int32 RoundCountDown;
	FTimerHandle GameRoundTimerHandle;

};
