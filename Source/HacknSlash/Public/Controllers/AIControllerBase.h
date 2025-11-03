// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <Interfaces/InterfaceController.h>
#include "AIControllerBase.generated.h"

/**
 * 
 */

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;
class UBehaviorTree;
class UBrainComponent;

UCLASS()
class HACKNSLASH_API AAIControllerBase : public AAIController , public IInterfaceController
{
	GENERATED_BODY()

	AAIControllerBase();
	virtual void Tick(float DeltaTime);
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual EAIStates GetAIState() override;
	virtual void SetStateAsPassive() override;
	virtual void SetStateAsAttacking() override;
	virtual void SetStateAsFrozen() override;
	virtual void SetStateAsDead() override;
	virtual void SetStateAsInvestigating(FVector Location) override;
	virtual void SetIsGettingHit(bool bIsGettingHit) override;
	virtual  UBrainComponent* GetBrainComp() override;
	
	//UFUNCTION()
	//virtual void OnPerceptionUpdated(const TArray<AActor*>& DetectedPawn);

	//bool CanSenseActor(AActor* Actor, EAISenses AISense, FAIStimulus& AIStimulus);
	//void HandleSenseSight(AActor* Actor);
	//void HandleSenseHearing(AActor* Actor, FVector Location);
	//void HandleSenseDamage();
private:
	//Variables
		//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* AIPerception;
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

protected:

	//Blackboard
	FName StateKeyName;
	FName PointOfInterestKeyName;
	FName AttackTargetKeyName;
	FName AttackRadiusKeyName;
	FName IsGettingHitKeyName;



};
