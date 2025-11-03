// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AIControllerBase.h"
#include "Interfaces/InterfaceCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AIPerceptionSystem.h"

 AAIControllerBase::AAIControllerBase()
{
	 PrimaryActorTick.bCanEverTick = true;

	 AttackTargetKeyName = "Target";
	 StateKeyName = "AIState";
	 PointOfInterestKeyName = "PointOfInterest";
}



void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (auto* CharacterInterface = Cast<IInterfaceCharacter>(InPawn))
	{
		BehaviorTree = CharacterInterface->GetBehaviorTree();
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString("BTSet"));
	}

	if (BehaviorTree)
	{
		UBlackboardComponent* b;
		UseBlackboard(BehaviorTree->GetBlackboardAsset(), b);
		Blackboard = b;
		RunBehaviorTree(BehaviorTree);
	}


}

EAIStates AAIControllerBase::GetAIState()
{
	if (Blackboard)
	{
		EAIStates State = static_cast<EAIStates>(Blackboard->GetValueAsEnum(StateKeyName));
		return State;
	}
	return EAIStates();
}

void AAIControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Blackboard && !Blackboard->GetValueAsObject(AttackTargetKeyName))
	{
		if (auto* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			Blackboard->SetValueAsObject(AttackTargetKeyName, PlayerCharacter);
		}
	}
}

UBrainComponent* AAIControllerBase::GetBrainComp()
{
	return nullptr;
}

void AAIControllerBase::SetStateAsPassive()
{
	if (Blackboard)
	{
		Blackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAIStates::EAIS_Passive));
	}
}

void AAIControllerBase::SetStateAsAttacking()
{

	if (Blackboard)
	{
		Blackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAIStates::EAIS_Attacking));
	}



}

void AAIControllerBase::SetStateAsFrozen()
{
	if (Blackboard)
	{
		Blackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAIStates::EAIS_Frozen));
	}
}

void AAIControllerBase::SetStateAsDead()
{
	if (Blackboard)
	{
		Blackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAIStates::EAIS_Dead));
	}
}

void AAIControllerBase::SetStateAsInvestigating(FVector Location)
{
	if (Blackboard)
	{
		Blackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAIStates::EAIS_Investigating));
		Blackboard->SetValueAsVector(PointOfInterestKeyName, Location);
	}
}

void AAIControllerBase::SetIsGettingHit(bool bIsGettingHit)
{
	if (Blackboard)
	{
		Blackboard->SetValueAsBool(IsGettingHitKeyName, bIsGettingHit);
	}
}
