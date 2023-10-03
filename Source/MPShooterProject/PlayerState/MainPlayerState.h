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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void AddToScore(float ScoreAmount);
	void AddToDefeats(int32 DefeatsAmount);

#pragma region Replication Notifies
	virtual void OnRep_Score() override;

	UFUNCTION() //OnRep FUNCTIONS ALWAYS NEED TO BE UFUNCTION!!!!
	virtual void OnRep_Defeats();
#pragma endregion

private:
	//Added UPROPERTY to ensure the pointer will star as nullptr,
	//not as undefined pointer (who has garbage data inside)
	UPROPERTY()
	class AMainCharacter* Character;
	UPROPERTY()
	class AMainPlayerController* Controller;

	UPROPERTY(ReplicatedUsing = OnRep_Defeats)
	int32 Defeats;
};
