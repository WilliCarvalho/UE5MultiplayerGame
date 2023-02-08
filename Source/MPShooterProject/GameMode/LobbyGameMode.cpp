// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

//first safest place to access the player controller that joined the game
void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	//Check How many players we have in the game
	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	if (NumberOfPlayers == 2)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			bUseSeamlessTravel = true;
			World->ServerTravel(FString("/Game/Maps/Map_Battle?listen"));
		}
	}
}