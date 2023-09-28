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
	virtual void PlayerEliminated(class AMainCharacter* EliminatedCharacter, class AMainPlayerController* VictimController, AMainPlayerController* AttackerController);
};
