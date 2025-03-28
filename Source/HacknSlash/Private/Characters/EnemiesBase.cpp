// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemiesBase.h"
#include <ActorComponents/CombatComponent_Enemy.h>
#include <ActorComponents/CombatComponent_Base.h>

// Sets default values
AEnemiesBase::AEnemiesBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CombatComponent = CreateDefaultSubobject<UCombatComponent_Enemy>(TEXT("CombatComponent"));

}

// Called when the game starts or when spawned
void AEnemiesBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemiesBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemiesBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UCombatComponent_Base* AEnemiesBase::GetCombatComponent()
{
	return CombatComponent;
}

UBehaviorTree* AEnemiesBase::GetBehaviorTree()
{
	return BehaviourTree;;
}

