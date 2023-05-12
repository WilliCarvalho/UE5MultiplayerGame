// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletShell.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ABulletShell::ABulletShell()
{
	PrimaryActorTick.bCanEverTick = true;

	BulletShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletShellMesh"));
	SetRootComponent(BulletShellMesh);
	BulletShellMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	BulletShellMesh->SetSimulatePhysics(true);
	BulletShellMesh->SetEnableGravity(true);
	BulletShellMesh->SetNotifyRigidBodyCollision(true); //Need to set these when Simulate physics is set to true
	ShellEjectionImpulse = 10.f;
}

void ABulletShell::BeginPlay()
{
	Super::BeginPlay();
	
	BulletShellMesh->OnComponentHit.AddDynamic(this, &ABulletShell::OnHit);
	BulletShellMesh->AddImpulse(GetActorForwardVector() * ShellEjectionImpulse);

	SetLifeSpan(3.f);
}

void ABulletShell::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(ShellSound && !SoundPlayed)
	{
		SoundPlayed = true;
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
	}
}

