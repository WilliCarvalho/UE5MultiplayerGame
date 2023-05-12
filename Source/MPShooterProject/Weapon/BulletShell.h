// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletShell.generated.h"

UCLASS()
class MPSHOOTERPROJECT_API ABulletShell : public AActor
{
	GENERATED_BODY()
	
public:
	ABulletShell();

protected:
	virtual void BeginPlay() override;

	UFUNCTION() // Important to be UFUNCTION() to be implemented to callbacks, delegates, etc.
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BulletShellMesh;

	UPROPERTY(EditAnywhere)
		float ShellEjectionImpulse;

	UPROPERTY(EditAnywhere)
	class USoundCue* ShellSound;

	bool SoundPlayed = false;
};
