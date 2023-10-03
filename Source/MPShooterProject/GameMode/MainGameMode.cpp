// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "MPShooterProject/Character/MainCharacter.h"
#include "MPShooterProject/PlayerController/MainPlayerController.h"
#include "MPShooterProject/PlayerState/MainPlayerState.h"

void AMainGameMode::PlayerEliminated(AMainCharacter* EliminatedCharacter, AMainPlayerController* VictimController,
                                     AMainPlayerController* AttackerController)
{
	AMainPlayerState* AttackerPlayerState = AttackerController ? Cast<AMainPlayerState>(AttackerController->PlayerState) : nullptr;
	AMainPlayerState* VictimPlayerState = VictimController ? Cast<AMainPlayerState>(VictimController->PlayerState) : nullptr;

	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState)
	{
		AttackerPlayerState->AddToScore(1.f);
	}
	
	if (EliminatedCharacter)
	{
		EliminatedCharacter->OnEliminated();
	}
}

void AMainGameMode::RequestRespawn(ACharacter* EliminatedCharacter, AController* EliminatedController)
{
	if (EliminatedCharacter)
	{
		EliminatedCharacter->Reset();
		EliminatedCharacter->Destroy();
	}
	if (EliminatedController)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(EliminatedController, PlayerStarts[Selection]);
	}
}
