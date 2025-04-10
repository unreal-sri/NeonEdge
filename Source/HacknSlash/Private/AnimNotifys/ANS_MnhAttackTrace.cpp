// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifys/ANS_MnhAttackTrace.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Interfaces/InterfaceCharacter.h"
#include "MissNoHit/Public/MnhTracerComponent.h"
#include "ActorComponents/CombatComponent_Base.h"
#include "Weapons/Weapon_Melee.h"
#include "GameplayTagContainer.h"
#include "Perception/AISense_Damage.h"

UANS_MnhAttackTrace::UANS_MnhAttackTrace()
{

	TracerTags = FGameplayTagContainer(FGameplayTag::RequestGameplayTag("R_PrimaryWeapon"));
}

void UANS_MnhAttackTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	// Attempt to cast the owner of the Mesh Component to a Character Interface
// Ensures that the owner implements IInterface_Character
	auto* CharacterInterface = Cast<IInterfaceCharacter>(MeshComp->GetOwner());
	// If the owner does not implement the character interface, exit the function early
	if (!CharacterInterface) return;
	// Retrieve the currently equipped item in the specified equipment slot (Melee slot)
	auto* EquippedWeapon = CharacterInterface->GetMeleeWeapon();
	// If no item is equipped in the melee slot, exit early
	if (!EquippedWeapon) return;
	Owner = MeshComp->GetOwner();
	ActorsToIgnore.AddUnique(MeshComp->GetOwner());
	ActorsToIgnore.AddUnique(EquippedWeapon);

	//mnh Tracer start
	EquippedWeapon->GetTracerComponent()->StartTracers(TracerTags);
	EquippedWeapon->GetTracerComponent()->OnHitDetected.AddDynamic(this, &UANS_MnhAttackTrace::OnHitDetected);

}

void UANS_MnhAttackTrace::OnHitDetected(FGameplayTag TracerTag, FHitResult HitResult, float DeltaTime)
{
	FDamageInfo DamageInfo;

	DamageInfo.HealthDamage = HealthDamage;
	DamageInfo.BalanceDamage = BalanceDamage;
	DamageInfo.bCanBeDodged = bCanBeDodged;
	DamageInfo.bOverrideDefaultHitResponse = bOverrideDefaultHitResponse;
	DamageInfo.OverridenDamageResponseMontage = OverridenDamageResponseMontage;
	DamageInfo.HitImpactNormal = HitResult.ImpactNormal;
	DamageInfo.ResponseType = ResponseType; 
	DamageInfo.DamageCauser = Owner;
	DamageInfo.LaunchSpeed = LaunchSpeed;


	if (auto* CharacterInterface = Cast<IInterfaceCharacter>(HitResult.GetActor()))
	{
		if (!(ActorsToIgnore.Contains(HitResult.GetActor())))
		{

			
			if (auto* CombatComp = CharacterInterface->GetCombatComponent())
			{
				if (//!CombatComp->IsOnSameTeam(Owner)
					true)
				{
					DamageInfo.HealthDamage = HealthDamage * CombatComp->StatsScale.SwordPower;
					DamageInfo.BalanceDamage = BalanceDamage * CombatComp->StatsScale.SwordPower;

					if (true)
					{
						DamageInfo.HitLocation = HitResult.ImpactPoint;
						DamageInfo.HitBoneName = HitResult.BoneName;
						CombatComp->TakeDamage(DamageInfo);
						UAISense_Damage::ReportDamageEvent(GetWorld(), HitResult.GetActor(), Owner, DamageInfo.HealthDamage, HitResult.Location, HitResult.Location);
					}

				}
			}
			ActorsToIgnore.AddUnique(HitResult.GetActor());
		}
	}
}


void UANS_MnhAttackTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
}

void UANS_MnhAttackTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	// Ensures that the owner implements IInterface_Character
	auto* CharacterInterface = Cast<IInterfaceCharacter>(MeshComp->GetOwner());
	// If the owner does not implement the character interface, exit the function early
	if (!CharacterInterface) return;

	// Retrieve the currently equipped item in the specified equipment slot (Melee slot)
	auto* EquippedWeapon = CharacterInterface->GetMeleeWeapon();
	// If no item is equipped in the melee slot, exit early
	if (!EquippedWeapon) return;

	EquippedWeapon->GetTracerComponent()->StopTracers(TracerTags);

	if (EquippedWeapon->GetTracerComponent()->OnHitDetected.IsAlreadyBound(this, &UANS_MnhAttackTrace::OnHitDetected))
	{
		EquippedWeapon->GetTracerComponent()->OnHitDetected.RemoveDynamic(this, &UANS_MnhAttackTrace::OnHitDetected);
	}

	ActorsToIgnore.Empty();
	CharacterInterface = nullptr;
	EquippedWeapon = nullptr;
}
