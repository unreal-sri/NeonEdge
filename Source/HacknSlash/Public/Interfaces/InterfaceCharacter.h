// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/States.h"
#include "Structs/Settings.h"
#include "InterfaceCharacter.generated.h"

class UActorComp_Gait;
class UActorComp_Inventory_Base;
class UCombatComponent_Base;
class UCombatComponent_Player;
class UCombatComponent_Enemy;
class UBehaviorTree;
class UCameraComponent;
class USpringArmComponent;
class UCharacterMovementComponent;
class UUW_MainOverlay;
class UMotionWarpingComponent;;
class AAIMovementPath;
class AWeapon_Melee;


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceCharacter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HACKNSLASH_API IInterfaceCharacter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//FORCEINLINE virtual void RecieveGait(EGait CurrentGait) {};
	
	FORCEINLINE virtual void RecieveIsAiming(bool InbIsAiming) { false; };
	FORCEINLINE virtual void RecieveIsSliding(bool InbIsSliding) { false; };
	FORCEINLINE virtual void RecieveIsDashing(bool InbIsDashing) { false; };
	FORCEINLINE virtual void RecievebIsJumpPressed(bool InbIsJumpPressed) { false; };
	FORCEINLINE virtual void RecieveDashDirection(FName InDashDirection) {};

	//UI

	//FORCEINLINE  virtual UUW_MainOverlay* GetMainOverlay() { return nullptr; };
	 
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//UUW_Stats* GetStatsWidget();

	FORCEINLINE virtual UCombatComponent_Base* GetCombatComponent() { return nullptr; };
	FORCEINLINE virtual UCombatComponent_Player* GetPlayerCombatComponent() { return nullptr; };
	FORCEINLINE virtual UCombatComponent_Enemy* GetEnemyCombatComponent() { return nullptr; };
	FORCEINLINE virtual EPlayerStates GetCurrentState() { return EPlayerStates::EPS_Passive;  };
	FORCEINLINE virtual AWeapon_Melee* GetMeleeWeapon() { return nullptr; };
	FORCEINLINE virtual UBehaviorTree* GetBehaviorTree() { return nullptr; };
	FORCEINLINE virtual UCameraComponent* GetFollowCameraComponent() { return nullptr; };
	FORCEINLINE virtual UMotionWarpingComponent* GetMotionWarpComponent() { return nullptr; };

	//Setters
   virtual void SetCurrentState(EPlayerStates State) {};

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//AAIMovementPath* GetAIMovementPath();


};
