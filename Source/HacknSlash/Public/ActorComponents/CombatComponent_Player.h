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
	





protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trace")
	TArray < TEnumAsByte < EObjectTypeQuery > > ObjectTypes;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace")
	TArray<AActor*> ActorsToIgnore;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Trace", meta = (MakeEditWidget = "true"))
	FVector Start;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace", meta = (MakeEditWidget = "true"))
	FVector End;

	FHitResult HitResult;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	ACharacter* EnemyInRange; 


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack||Combo", meta = (AllowPrivateAccess = "true"));
	bool bSwitchCombo;


	

};
