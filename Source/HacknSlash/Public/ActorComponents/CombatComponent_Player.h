// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/CombatComponent_Base.h"
#include "CombatComponent_Player.generated.h"

/**
 * 
 */

class ACharacter;



UCLASS()
class HACKNSLASH_API UCombatComponent_Player : public UCombatComponent_Base
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UCombatComponent_Player();


private:


	virtual bool TakeDamage(FDamageInfo DamageInfo) override;

	//virtual void NormalDamageResponse(bool bOverrideDefaultHitResponse, UAnimMontage* OverridenDamageResponseMontage, float LaunchSpeed, FVector HitLocation, AActor* DamageCauser, FName HitDirectionName)override;
	UFUNCTION(BlueprintCallable)
	void RotateCharacterInterp();
	FRotator NewCharRotation;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



	EPlayerStates PlayerState;

	ACharacter* OwningCharacter;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TraceForNearbyEnemies(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void PerformLightAttack(int32 Index);

	UFUNCTION(BlueprintPure)
	bool CanAttack();

	UFUNCTION(BlueprintPure)
	bool CanDodge();

	UFUNCTION(BlueprintCallable)
	void PerformHeavyAttack(int32 Index);

	UFUNCTION(BlueprintCallable)
	void PerformDodge(UAnimMontage* Dodge);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace")
	TArray<AActor*> ActorsToIgnore;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Trace", meta = (MakeEditWidget = "true"))
	FVector Start;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace", meta = (MakeEditWidget = "true"))
	FVector End;

	
	TArray<FHitResult> HitResult;
	UPROPERTY(VisibleAnywhere)
	float ShortestDistanceToEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	ACharacter* EnemyInRange; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 LightAttackIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 HeavyAttackIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 ComboStarterIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TArray <UAnimMontage*> LightAttackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TArray <UAnimMontage*> HeavyAttackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TArray <UAnimMontage*> ComboStarterMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TArray <UAnimMontage*> ComboExtenderMontages;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack|Combo");
	bool bSwitchLightCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack|Combo");
	bool bSwitchHeavyCombo;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack|Dodge");
	bool bContinueDodge;

};
