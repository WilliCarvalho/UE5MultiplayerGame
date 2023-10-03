// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MPSHOOTERPROJECT_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	void AddToScore(float ScoreAmount);
	virtual void OnRep_Score() override;
private:
	class AMainCharacter* Character;
	class AMainPlayerController* Controller;
};
