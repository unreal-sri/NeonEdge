// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Enums/States.h"
#include <GameplayTagContainer.h>
#include "ANS_MnhAttackTrace.generated.h"

/**
 * 
 */
UCLASS()
class HACKNSLASH_API UANS_MnhAttackTrace : public UAnimNotifyState
{
	GENERATED_BODY()
public:

	UANS_MnhAttackTrace();

protected:

	FVector StartLoc;
	FVector EndLoc;
	AActor* Owner;

	TArray<AActor*> ActorsToIgnore;

	// Pointer to hold the trail particle component
	UParticleSystemComponent* TrailParticleComponent;

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer TracerTags;

	UPROPERTY(EditAnywhere)
	float HealthDamage = 10.0f;

	UPROPERTY(EditAnywhere)
	float BalanceDamage = 10.0f;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	bool bCanBeBlocked = true;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	bool bCanBeParried = true;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	bool bCanBeDodged = true;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	float LaunchSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	bool bOverrideDefaultHitResponse;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	UAnimMontage* OverridenDamageResponseMontage;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	EDamageResponse ResponseType = EDamageResponse::EDR_NormalHit;

	UPROPERTY(EditAnywhere)
	FName HandPreferenceTag = "Default";


	UFUNCTION()
	void OnHitDetected(FGameplayTag TracerTag, FHitResult HitResult, float DeltaTime);
	
	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);

	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);

	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

};
