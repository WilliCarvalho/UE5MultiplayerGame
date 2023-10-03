// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerState.h"

#include "MPShooterProject/Character/MainCharacter.h"
#include "MPShooterProject/PlayerController/MainPlayerController.h"
#include "Net/UnrealNetwork.h"

void AMainPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMainPlayerState, Defeats);
}

void AMainPlayerState::AddToScore(float ScoreAmount)
{
	SetScore(GetScore() + ScoreAmount);
	Character = Character == nullptr ? Cast<AMainCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AMainPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(GetScore());
		}
	}
}

void AMainPlayerState::AddToDefeats(int32 DefeatsAmount)
{
	Defeats += DefeatsAmount;
	Character = Character == nullptr ? Cast<AMainCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AMainPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDefeats(Defeats);
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
			Controller->SetHUDScore(GetScore());
		}
	}
}

void AMainPlayerState::OnRep_Defeats()
{
	Character = Character == nullptr ? Cast<AMainCharacter>(GetPawn()) : Character;
	if (Character && Character->Controller)
	{
		Controller = Controller == nullptr ? Cast<AMainPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDefeats(Defeats);
		}
	}
}
