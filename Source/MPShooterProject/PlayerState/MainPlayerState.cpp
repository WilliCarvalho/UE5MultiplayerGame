// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerState.h"

#include "MPShooterProject/Character/MainCharacter.h"
#include "MPShooterProject/PlayerController/MainPlayerController.h"

void AMainPlayerState::AddToScore(float ScoreAmount)
{
	SetScore(GetScore() + ScoreAmount);
	Character = Character == nullptr ? Cast<AMainCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AMainPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHudScore(GetScore());
		}
	}
}

void AMainPlayerState::OnRep_Score()
{
	Super::OnRep_Score();
	Character = Character == nullptr ? Cast<AMainCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AMainPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHudScore(GetScore());
		}
	}
}
