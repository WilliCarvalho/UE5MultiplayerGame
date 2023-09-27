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
	
protected:
	virtual void BeginPlay() override;

private:
	class AMainHUD* MainHUD;
};
