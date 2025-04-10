// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Interfaces/InterfaceCharacter.h>
#include "InputActionValue.h"
#include "MainPlayer.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UMotionWarpingComponent;
class UCombatComponent_Player;
class AWeapon_Melee;


UCLASS()
class HACKNSLASH_API AMainPlayer : public ACharacter , public IInterfaceCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	virtual UCombatComponent_Player* GetPlayerCombatComponent() override;
	virtual AWeapon_Melee* GetMeleeWeapon() override;

	UFUNCTION(BlueprintPure)
	 virtual EPlayerStates GetCurrentState () override;

	 UFUNCTION(BlueprintCallable)
	 virtual void SetCurrentState(EPlayerStates State) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Input Functions
	void ActionLook(const FInputActionValue& Value);
	void ActionMove(const FInputActionValue& Value);
	void ActionJump(const FInputActionValue& Value);
	void ActionStopJump(const FInputActionValue& Value);
	void ActionLightAttack(const FInputActionValue& Value);
	void ActionHeavyAttack(const FInputActionValue& Value);
	void ActionDodge(const FInputActionValue& Value);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private: 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCombatComponent_Player* CombatComponent; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerStates CurrentState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AWeapon_Melee* MeleeWeapon;
private:
	//Montages
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DodgeMontage;

	


	//Input
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IMC_Player;

	UPROPERTY(EditDefaultsOnly, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_LightAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_HeavyAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Dodge;

	UPROPERTY(EditDefaultsOnly, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_RangedAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Input", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_AbilityKey;

	//Sensitivity
	UPROPERTY(EditDefaultsOnly, Category = "Sensitivity", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	UPROPERTY(EditDefaultsOnly, Category = "Sensitivity", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

public:


};
