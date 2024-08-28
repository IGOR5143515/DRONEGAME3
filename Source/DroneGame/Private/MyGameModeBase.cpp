// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "DroneCharacter.h"
#include "MyAIController.h"
#include "MyPlayerController.h"
#include "CharacterPlayerState.h"


AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = ADroneCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	PlayerStateClass = ACharacterPlayerState::StaticClass();

}

void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();

	CreateTeamsInfo();
	SpawnBots();
	CurrentRound = 1;
	StartRound();

}

UClass* AMyGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AMyAIController>()) {
		return AIPawnClass;
	}
	else
		return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AMyGameModeBase::SpawnBots()
{
	if (!GetWorld())return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; i++) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto AIController=GetWorld()->SpawnActor<AMyAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(AIController);
	}
	
}

void AMyGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AMyGameModeBase::GameTimerUpdate, 1.0f, true);
}

void AMyGameModeBase::GameTimerUpdate()
{

	UE_LOG(LogTemp, Error, TEXT("Time %i / Round %i / %i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

	
	if (--RoundCountDown == 0) {
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum) {
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
			UE_LOG(LogTemp, Error, TEXT("Game Ower"));
	}
}

void AMyGameModeBase::ResetPlayers()
{

	if (!GetWorld())return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It) {

		ResetOnePlayer(It->Get());
	
	}

}

void AMyGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetWorld()) {
		Controller->GetPawn()->Reset();
	}

	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void AMyGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld())return;

	int32 TeamID = 1;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It) {

		UE_LOG(LogTemp, Error, TEXT("TeamInfo"));

		 auto Controller = It->Get();
		if (!Controller)continue;

		 auto PlayerState = Cast<ACharacterPlayerState>(Controller->PlayerState);
		if (!PlayerState)continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);

		TeamID = TeamID == 1 ? 2 : 1;
	}
}

void AMyGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller)return;
	const auto Character = Cast<ADroneCharacter>(Controller->GetPawn());
	if (!Character)return;

	const auto PlayerState = Cast<ACharacterPlayerState>(Controller->PlayerState);
	if (!PlayerState)return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

FLinearColor AMyGameModeBase::DetermineColorByTeamID(  int32 TeamID) 
{
	if (TeamID - 1 < GameData.TeamColors.Num()) {
		return GameData.TeamColors[TeamID - 1];
	}
	return GameData.DefaultTeamColor;
}
