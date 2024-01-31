// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MPSHOOTERPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetHUDHealth(float CurrentHealth, float MaxHealth);
	void SetHUDScore(float Score);
	void SetHUDDefeats(int32 Defeats);
	void SetHUDWeaponAmmo(int32 Amount);
	void SetHUDCarriedAmmo(int32 Amount);
	void SetHUDMatchCountdown(float CountdownTime);
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay() override;
	void SetHUDTime();
private:
	class AMainHUD* MainHUD;

	float MatchTime = 120.f;
	uint32 CountdownInt;
};
