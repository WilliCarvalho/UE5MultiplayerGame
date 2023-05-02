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

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BulletShellMesh;

protected:
	virtual void BeginPlay() override;


};
