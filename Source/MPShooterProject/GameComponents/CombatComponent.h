// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

//Can forward declare a class here as well

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MPSHOOTERPROJECT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	friend class AMainCharacter;

	void EquipWeapon(class AWeapon* WeaponToEquip);
protected:
	virtual void BeginPlay() override;
	 
private:
	class AMainCharacter* Character;
	AWeapon* EquippedWeapon;

public:

		
};
