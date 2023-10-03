// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "MPShooterProject/CharacterTypes/TurningInPlace.h"
#include "MPShooterProject/Interfaces/InteractWithCrosshairInterface.h"
#include "MainCharacter.generated.h"

UCLASS()
class MPSHOOTERPROJECT_API AMainCharacter : public ACharacter, public IInteractWithCrosshairInterface
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called to bind functionality to input
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	void PlayFireMontage(bool bAiming);
	void PlayEliminationMontage();

	virtual void OnRep_ReplicatedMovement() override;
	void OnEliminated();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnEliminated();
	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;

	void MoveFoward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void EquippButtonPressed();
	void CrouchButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();
	void CalculateAO_Pitch();
	void AimOffset(float DeltaTime);
	void SimProxiesTurn();
	virtual void Jump() override;
	void FireButtonPressed();
	void FireButtonReleased();
	void PlayHitReactMontage();

	UFUNCTION() //again - needs to be UFUNCTION to receive delegate callbacks
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                   class AController* InstigatorController, AActor* DamageCauser);
	void UpdateHUDHealth();
	// Pool for any relevant classes and initialize our HUD
	void PoolInit();

private:
	UPROPERTY(visibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(visibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon) //Replicated using the function OnRep_OverlappingWeapon
	class AWeapon* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UPROPERTY(VisibleAnywhere)
	class UCombatComponent* CombatComponent;

	//Reliable - garantee will be executed
	//Unreliable - can be dropped and not be executed
	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartAimRotation;

	ETurningInPlace TurningInPlace;
	void TurnInPlace(float DeltTime);

	UPROPERTY(EditAnywhere, Category = Combat)
	class UAnimMontage* FireWeaponMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	class UAnimMontage* HitReactionMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	class UAnimMontage* EliminationMontage;

	void HideCameraIfCharacterClose();

	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;

	bool bRotateRootBone;
	float TurnThreshold = 0.5f;
	FRotator ProxyRotationLastFrame;
	FRotator ProxyRotation;
	float ProxyYaw;
	float TimeSinceLastMovementReplication;
	float CalculateSpeed();

#pragma region Player health and elimination
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;

	//Variable replication is better than use RPC - take less data transfer through internet
	UPROPERTY(ReplicatedUsing = Onrep_Health, VisibleAnywhere, Category = "Player Stats")
	float CurrentHealth = 100.f;

	UFUNCTION()
	void OnRep_Health();

	class AMainPlayerController* MainPlayerController;

	bool bEliminated = false;

	FTimerHandle ElimTimer;

	UPROPERTY(EditDefaultsOnly)
	float ElimDelay = 3.f;
	void ElimTimerFinished();
#pragma endregion

#pragma region Dissolve Effect
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DissolveTimeline;
	FOnTimelineFloat DissolveTrack;

	UPROPERTY(EditAnywhere)
	UCurveFloat* DissolveCurve;

	UFUNCTION()
	void UpdateDissolveMaterial(float DissolveValue);
	void StartDissolve();

	//Dynamic instance that we can change at runtime
	UPROPERTY(VisibleAnywhere, Category = Elimination)
	UMaterialInstanceDynamic* DynamicDissolveMaterialInstance;

	// Material instance set on the Blueprint, used with the dynamic material instance
	UPROPERTY(EditAnywhere, Category = Elimination)
	UMaterialInstance* DissolveMaterialInstance;
#pragma endregion

#pragma region Elimination bot
	UPROPERTY(EditAnywhere)
	UParticleSystem* EliminationBotEffect;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EliminationBotComponent;

	UPROPERTY(EditAnywhere)
	class USoundCue* EliminationBotSound;
#pragma endregion

	UPROPERTY()
	class AMainPlayerState* MainPlayerState;

public:
	void SetOverlappingWeapon(AWeapon* Weapon);
	bool IsWeaponEquipped();
	bool IsAiming();
	AWeapon* GetEquippedWeapon();
	FVector GetHitTarget() const;
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }
	FORCEINLINE bool IsEliminated() const { return bEliminated; }
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
};
