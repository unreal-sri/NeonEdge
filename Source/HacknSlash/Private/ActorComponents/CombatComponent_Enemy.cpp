// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/CombatComponent_Enemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/InterfaceController.h"



void UCombatComponent_Enemy::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComponent_Enemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent_Enemy::NormalDamageResponse(FDamageInfo DamageInfo, FName HitDirectionName)
{
	Super::NormalDamageResponse(DamageInfo, HitDirectionName);

	/*if (StatsWidget)
	{
		StatsWidget->UpdateHealthWidget(GetHealthPercent());
		StatsWidget->UpdateBalanceWidget(GetBalancePercent());
	}*/
	if(auto * ControllerInterface = Cast<IInterfaceController>(GetOwningCharacter()->GetController()))
	{
		ControllerInterface->SetIsGettingHit(true);
		ControllerInterface->SetStateAsFrozen();
	}
	if (DamageInfo.bIsAirBone)
	{
		bIsAirbone = true;
		AnimInstance->Montage_Play(LaunchAirHitReactMontage);
		OwningCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		// Bind montage end delegate to unlock movement
		FOnMontageEnded MontageEndDelegate;
		MontageEndDelegate.BindUObject(this, &UCombatComponent_Base::OnDamageResponseMontageEnded);
		AnimInstance->Montage_SetEndDelegate(MontageEndDelegate,LaunchAirHitReactMontage);
		return;
	}

	if (bIsAirbone)
	{
		AnimInstance->Montage_Play(AirHitReactMontage);
		OwningCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		FOnMontageEnded MontageEndDelegate;
		MontageEndDelegate.BindUObject(this, &UCombatComponent_Base::OnDamageResponseMontageEnded);
		AnimInstance->Montage_SetEndDelegate(MontageEndDelegate, LaunchAirHitReactMontage);
		return;
	}

	

}

void UCombatComponent_Enemy::OnDamageResponseMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnDamageResponseMontageEnded(Montage, bInterrupted);

	if (auto* ControllerInterface = Cast<IInterfaceController>(GetOwningCharacter()->GetController()))
	{
		ControllerInterface->SetIsGettingHit(false);
		ControllerInterface->SetStateAsPassive();
	}

	if (bIsAirbone && !bInterrupted )
	{
		OwningCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		bIsAirbone = false;
	}

}

