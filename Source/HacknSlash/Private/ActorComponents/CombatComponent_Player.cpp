// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/CombatComponent_Player.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/InterfaceCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


UCombatComponent_Player::UCombatComponent_Player()
{
	PrimaryComponentTick.bCanEverTick = true;  // Allows ticking for this component
}

void UCombatComponent_Player::BeginPlay()
{

	ActorsToIgnore.Add(GetOwner());
	OwningCharacter = Cast<ACharacter>(GetOwner());


}

void UCombatComponent_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	TraceForNearbyEnemies(DeltaTime);
	
	
	//ROtating Character
	if (NewCharRotation != FRotator(0.f) && Cast<IInterfaceCharacter>(GetOwner())->GetCurrentState() == EPlayerStates::EPS_Attack && !EnemyInRange)
	{
		RotateCharacterInterp();
	}
	
}

void UCombatComponent_Player::TraceForNearbyEnemies(float DeltaTime)
{
	//settings start and end trace distances
	Start = GetOwner()->GetActorLocation();
	auto* PlayerController = GetOwner()->GetInstigator()->GetController();
	FVector ViewPointLoc;
	FRotator ViewPointRot;
	PlayerController->GetPlayerViewPoint(ViewPointLoc, ViewPointRot);
	ViewPointLoc = FVector(ViewPointLoc.X, ViewPointLoc.Y, GetOwner()->GetActorLocation().Z);
	ViewPointRot.Pitch = 0.f;
	FVector New = UKismetMathLibrary::GetForwardVector(ViewPointRot) * 700.f;

	End = ViewPointLoc + New;

	UKismetSystemLibrary::CapsuleTraceMultiByProfile(GetWorld(), Start, End, 90.f, 88.f, "Enemy", false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResult, true);
	//Set the enemy to snap to
	if (!(HitResult.Num() == 0))
	{

		for (int32 i = 0; i < HitResult.Num(); i++)
		{
			
			if (i == 0)
			{
				EnemyInRange = nullptr;
				ShortestDistanceToEnemy = 600.f;
			}
			
			if (GetOwner()->GetDistanceTo(HitResult[i].GetActor()) < ShortestDistanceToEnemy)
			{
				ShortestDistanceToEnemy = GetOwner()->GetDistanceTo(HitResult[i].GetActor());
				EnemyInRange = Cast<ACharacter>(HitResult[i].GetActor());
				GEngine->AddOnScreenDebugMessage(2, DeltaTime, FColor::Black, FString::Printf(TEXT("Target Enemy:%s"), *EnemyInRange->GetName()));
			}
			// Access element with MyArray[i]
			GEngine->AddOnScreenDebugMessage(3, DeltaTime, FColor::Cyan, FString::Printf(TEXT("Shortest Distance:%f"),ShortestDistanceToEnemy));
			GEngine->AddOnScreenDebugMessage(1, DeltaTime, FColor::Black, FString::Printf(TEXT("Number Of Hits:%d"), HitResult.Num()));
		}
	}
	else if (HitResult.Num() == 0)
	{
		EnemyInRange = nullptr;
		ShortestDistanceToEnemy = 600.f;
	}
}

bool UCombatComponent_Player::TakeDamage(FDamageInfo DamageInfo)
{
	return false;
}

void UCombatComponent_Player::RotateCharacterInterp()
{
	if (NewCharRotation != FRotator(0.f))
	{
		NewCharRotation.Roll = 0.f;
		NewCharRotation.Pitch = 0.f;
		OwningCharacter->SetActorRotation(FMath::RInterpTo(OwningCharacter->GetActorRotation(), NewCharRotation, GetWorld()->GetDeltaSeconds(), 10.f));
		if (OwningCharacter->GetActorRotation() ==  NewCharRotation)
		{
			NewCharRotation = FRotator(0.f);
		}
	}
}

void UCombatComponent_Player::PerformLightAttack(int32 Index)
{
	if (Index >= LightAttackMontages.Num())
	{

		LightAttackIndex = 0;
	}

	if (UAnimMontage* LightAttack = LightAttackMontages[LightAttackIndex])
	{
		if (auto* CharacterInterface = Cast<IInterfaceCharacter>(GetOwner()))
		{
			CharacterInterface->SetCurrentState(EPlayerStates::EPS_Attack);
			OwningCharacter->GetMesh()->GetAnimInstance()->Montage_Play(LightAttack);
			LightAttackIndex += 1;
			if (!EnemyInRange)
			{
				//Creating a Rotator based on last input
				FRotator Rotator = FRotationMatrix::MakeFromX(OwningCharacter->GetCharacterMovement()->GetLastInputVector()).Rotator();
				//If the input is valid a tick function starts to rotate character facing that direction
				NewCharRotation = OwningCharacter->GetCharacterMovement()->GetLastInputVector() != FVector(0.f) ? Rotator : FRotator(0.f);
			}
			

		}
		LightAttack = nullptr;
	}

}

bool UCombatComponent_Player::CanAttack()
{
	if (auto* CharacterInterface = Cast<IInterfaceCharacter>(GetOwner()))
	{
		//States where cannot attack
		if (CharacterInterface->GetCurrentState() == EPlayerStates::EPS_Attack || CharacterInterface->GetCurrentState() == EPlayerStates::EPS_Dodge ||
			CharacterInterface->GetCurrentState()== EPlayerStates::EPS_Frozen || CharacterInterface->GetCurrentState() == EPlayerStates::EPS_Dead || OwningCharacter->GetCharacterMovement()->IsFalling())
		{
			return false;
		}
		return true;
	}
	return false;
}

bool UCombatComponent_Player::CanDodge()
{
	if (auto* CharacterInterface = Cast<IInterfaceCharacter>(GetOwner()))
	{
		//States where cannot Dodge
		if (CharacterInterface->GetCurrentState() == EPlayerStates::EPS_Attack || CharacterInterface->GetCurrentState() == EPlayerStates::EPS_Dodge ||
			CharacterInterface->GetCurrentState() == EPlayerStates::EPS_Frozen || CharacterInterface->GetCurrentState() == EPlayerStates::EPS_Dead || OwningCharacter->GetCharacterMovement()->IsFalling())
		{
			return false;
		}
		return true;
	}
	return false;
}

void UCombatComponent_Player::PerformHeavyAttack(int32 Index)
{
	if (Index >= HeavyAttackMontages.Num())
	{

		HeavyAttackIndex = 0;
	}

	if (UAnimMontage* HeavyAttack = HeavyAttackMontages[HeavyAttackIndex])
	{
		if (auto* CharacterInterface = Cast<IInterfaceCharacter>(GetOwner()))
		{
			CharacterInterface->SetCurrentState(EPlayerStates::EPS_Attack);
			OwningCharacter->GetMesh()->GetAnimInstance()->Montage_Play(HeavyAttack);
			HeavyAttackIndex += 1;

			//Creating a Rotator based on last input
			FRotator Rotator = FRotationMatrix::MakeFromX(OwningCharacter->GetCharacterMovement()->GetLastInputVector()).Rotator();
			//If the input is valid a tick function starts to rotate character facing that direction
			NewCharRotation = OwningCharacter->GetCharacterMovement()->GetLastInputVector() != FVector(0.f) ? Rotator : FRotator(0.f);

		}
	}

}

void UCombatComponent_Player::PerformDodge(UAnimMontage* Dodge)
{
	if (auto* CharacterInterface = Cast<IInterfaceCharacter>(GetOwner()))
	{
		CharacterInterface->SetCurrentState(EPlayerStates::EPS_Dodge);
		OwningCharacter->GetMesh()->GetAnimInstance()->Montage_Play(Dodge);
	}

}


