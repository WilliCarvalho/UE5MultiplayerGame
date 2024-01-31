// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MPShooterProject/Character/MainCharacter.h"
#include "MPShooterProject/HUD/CharacterOverlay.h"
#include "MPShooterProject/HUD/MainHUD.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	MainHUD = Cast<AMainHUD>(GetHUD());
}

void AMainPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SetHUDTime();
}

void AMainPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AMainCharacter* MainCharacter = Cast<AMainCharacter>(InPawn);
	if (MainCharacter)
	{
		SetHUDHealth(MainCharacter->GetCurrentHealth(), MainCharacter->GetMaxHealth());
	}
}

void AMainPlayerController::SetHUDHealth(float CurrentHealth, float MaxHealth)
{
	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(GetHUD()) : MainHUD;
	bool bHUDValid = MainHUD &&
		MainHUD->CharacterOverlay &&
		MainHUD->CharacterOverlay &&
		MainHUD->CharacterOverlay->HealthBar &&
		MainHUD->CharacterOverlay->HealthText;
	if (bHUDValid)
	{
		const float HealthPercent = CurrentHealth / MaxHealth;
		MainHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
		FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(CurrentHealth),
		                                     FMath::CeilToInt(MaxHealth));
		MainHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
}

void AMainPlayerController::SetHUDScore(float Score)
{
	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(GetHUD()) : MainHUD;
	bool bHUDValid = MainHUD &&
		MainHUD->CharacterOverlay &&
		MainHUD->CharacterOverlay &&
		MainHUD->CharacterOverlay->HealthBar &&
		MainHUD->CharacterOverlay->HealthText;
	if (bHUDValid)
	{
		FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Score));
		MainHUD->CharacterOverlay->ScoreAmount->SetText(FText::FromString(ScoreText));
	}
}

void AMainPlayerController::SetHUDDefeats(int32 Defeats)
{
	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(GetHUD()) : MainHUD;
	bool bHUDValid = MainHUD &&
		MainHUD->CharacterOverlay &&
		MainHUD->CharacterOverlay->DefeatsAmount;
	if (bHUDValid)
	{
		FString DefeatsText = FString::Printf(TEXT("%d"), Defeats);
		MainHUD->CharacterOverlay->DefeatsAmount->SetText(FText::FromString(DefeatsText));
	}
}

void AMainPlayerController::SetHUDWeaponAmmo(int32 Amount)
{
	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(GetHUD()) : MainHUD;
	bool bHUDValid = MainHUD &&
		MainHUD->CharacterOverlay &&
		MainHUD->CharacterOverlay->WeaponAmmoAmount;
	if (bHUDValid)
	{
		FString WeaponAmmoAmountText = FString::Printf(TEXT("%d"), Amount);
		MainHUD->CharacterOverlay->WeaponAmmoAmount->SetText(FText::FromString(WeaponAmmoAmountText));
	}
}

void AMainPlayerController::SetHUDCarriedAmmo(int32 Amount)
{
	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(GetHUD()) : MainHUD;
	bool bHUDValid = MainHUD &&
		MainHUD->CharacterOverlay &&
		MainHUD->CharacterOverlay->CarriedAmmoAmount;
	if (bHUDValid)
	{
		FString CarriedAmmoAmountText = FString::Printf(TEXT("%d"), Amount);
		MainHUD->CharacterOverlay->CarriedAmmoAmount->SetText(FText::FromString(CarriedAmmoAmountText));
	}
}

void AMainPlayerController::SetHUDMatchCountdown(float CountdownTime)
{
	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(GetHUD()) : MainHUD;
	bool bHUDValid = MainHUD &&
		MainHUD->CharacterOverlay &&
		MainHUD->CharacterOverlay->MatchCountdownText;
	if (bHUDValid)
	{
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60);
		int32 Seconds = CountdownTime - Minutes * 60;

		FString CountDownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		MainHUD->CharacterOverlay->MatchCountdownText->SetText(FText::FromString(CountDownText));
	}
}

void AMainPlayerController::SetHUDTime()
{
	uint32 SecondsLeft = FMath::CeilToInt(MatchTime - GetWorld()->GetTimeSeconds());
	if (CountdownInt != SecondsLeft)
	{
		SetHUDMatchCountdown(MatchTime - GetWorld()->GetTimeSeconds());
	}

	CountdownInt = SecondsLeft;
}