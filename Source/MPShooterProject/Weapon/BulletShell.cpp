// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletShell.h"

ABulletShell::ABulletShell()
{
	PrimaryActorTick.bCanEverTick = true;

	BulletShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletShellMesh"));
	SetRootComponent(BulletShellMesh);
}

void ABulletShell::BeginPlay()
{
	Super::BeginPlay();
	
}

