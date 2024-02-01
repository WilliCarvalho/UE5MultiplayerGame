// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MPSHOOTERPROJECT_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AMainGameMode();
	virtual void Tick(float DeltaSeconds) override;
	virtual void PlayerEliminated(class AMainCharacter* EliminatedCharacter, class AMainPlayerController* VictimController, AMainPlayerController* AttackerController);
	virtual void RequestRespawn(ACharacter* EliminatedCharacter, AController* EliminatedController);

	UPROPERTY(EditDefaultsOnly)
	float WarmupTime = 10.f;

private:
	float CountDownTime = 0.f;

	float LevelStartingTime = 0.f;
protected:
	virtual void BeginPlay() override;
};
