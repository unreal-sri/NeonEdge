// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/CombatComponent_Base.h"
#include "CombatComponent_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class HACKNSLASH_API UCombatComponent_Enemy : public UCombatComponent_Base
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void NormalDamageResponse(FDamageInfo Damageinfo, FName HitDirectionName)override;
	virtual void OnDamageResponseMontageEnded(UAnimMontage* Montage, bool bInterrupted)override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages|Combat")
	UAnimMontage* LaunchAirHitReactMontage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages|Combat")
	UAnimMontage* AirHitReactMontage;

private:

	FVector LaunchLoc;

};
