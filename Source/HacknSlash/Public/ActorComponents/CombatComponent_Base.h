// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/States.h"
#include "Structs/Settings.h"
#include "CombatComponent_Base.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamage, FDamageInfo, DamageInfo);

class ACharacter;
class UNiagaraSystem;
class UMaterialInterface;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKNSLASH_API UCombatComponent_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent_Base();

protected:

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;



	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	ACharacter* OwningCharacter;
	UAnimInstance* AnimInstance;

public:

	UFUNCTION(BlueprintCallable)
	virtual bool TakeDamage(FDamageInfo DamageInfo);
	virtual void Die();

	virtual void NormalDamageResponse(FDamageInfo DamageInfo, FName HitDireactionName);
	/*virtual void BlockDamageResponse(bool bOverrideDefaultHitResponse, UAnimMontage* OverridenDamageResponseMontage, bool bOverrideDefaultParryResponse, UAnimMontage* OverridenParryResponseMontage, float LaunchSpeed, FVector HitLocation);
	virtual void GotParriedDamageResponse(bool bOverrideDefaultHitResponse, UAnimMontage* OverridenDamageResponseMontage);*/

public:
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamage OnTakeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages|Combat")
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages|Combat")
	UAnimMontage* DownHitReactMontage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages|Combat")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages|Combat")
	bool bIsDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages|Combat")
	bool bIsAirbone;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages|Combat")
	float DownHitImpact = 400.f;
	// Character Stats

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FActorStats Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FActorStatsScale StatsScale;

	UPROPERTY(EditAnywhere, Category = "Particles", BlueprintReadOnly)
	TArray <UNiagaraSystem*> Niagara_Blood_Particles;

	UPROPERTY(EditAnywhere, Category = "Particles", BlueprintReadOnly)
	UMaterialInterface* Niagara_Blood_Decals;
	UPROPERTY(EditAnywhere, Category = "Particles", BlueprintReadOnly)
	FVector BloodDecalScale;

	UPROPERTY(EditAnywhere, Category = "Sounds", BlueprintReadOnly)
	USoundBase* NormalHit_Sound;

public:	
	void CalculateHitDirection(FVector DamageCauserLocation, FName& Section);
	virtual void OnDamageResponseMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	FORCEINLINE ACharacter* GetOwningCharacter() { return OwningCharacter; }

		
};
