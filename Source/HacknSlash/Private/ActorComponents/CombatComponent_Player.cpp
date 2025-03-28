// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/CombatComponent_Player.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


UCombatComponent_Player::UCombatComponent_Player()
{
	PrimaryComponentTick.bCanEverTick = true;  // Allows ticking for this component
}

void UCombatComponent_Player::BeginPlay()
{

	ActorsToIgnore.Add(GetOwner());

}

void UCombatComponent_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Black, FString::Printf(TEXT("Actor Name:")));
	Start = GetOwner()->GetActorLocation();
	auto* PlayerController = GetOwner()->GetInstigator()->GetController();
	FVector ViewPointLoc;
	FRotator ViewPointRot;
	PlayerController->GetPlayerViewPoint(ViewPointLoc, ViewPointRot);
	ViewPointLoc = FVector(ViewPointLoc.X, ViewPointLoc.Y, GetOwner()->GetActorLocation().Z);
	ViewPointRot.Pitch = 0.f;
	FVector New = UKismetMathLibrary::GetForwardVector(ViewPointRot) * 800.f;

	 End = ViewPointLoc + New;
	
	UKismetSystemLibrary::CapsuleTraceSingleForObjects(GetWorld(), Start, End, 100.f, 88.f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
	if (!EnemyInRange || EnemyInRange != HitResult.GetActor())
	{
		EnemyInRange = Cast<ACharacter>( HitResult.GetActor());
	}
	
	

}

bool UCombatComponent_Player::TakeDamage(FDamageInfo DamageInfo)
{
	return false;
}


