// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/CombatComponent_Base.h"
#include "Interfaces/InterfaceCharacter.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "MotionWarpingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"

// Sets default values for this component's properties
UCombatComponent_Base::UCombatComponent_Base()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UCombatComponent_Base::TakeDamage(FDamageInfo DamageInfo)
{
	
	// alive or dead
	GEngine->AddOnScreenDebugMessage(3, 4.f, FColor::Blue, FString::Printf(TEXT("DamageCauser: %s"), DamageInfo.DamageCauser));
	if (Stats.Health <= 0.f)
	{
		return false;
	}

	
	else if (Stats.Health > 0.f)
	{
		// Get the character interface of the damage causer
		IInterfaceCharacter* TargetCharacterInterface = Cast<IInterfaceCharacter>(DamageInfo.DamageCauser);
		if (!TargetCharacterInterface)
		{
			return false; // No valid damage causer, return
		}
		OnTakeDamage.Broadcast(DamageInfo);
		
		FName HitDirectionName = FName("");
		
		CalculateHitDirection(DamageInfo.DamageCauser->GetActorLocation(), HitDirectionName);
		Stats.Health -= DamageInfo.HealthDamage;
		NormalDamageResponse(DamageInfo.bOverrideDefaultHitResponse, DamageInfo.OverridenDamageResponseMontage, DamageInfo.HitLocation,DamageInfo.HitImpactNormal, DamageInfo.DamageCauser, HitDirectionName);
		return true;
	}
	
	return false;
}




// Called when the game starts
void UCombatComponent_Base::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// Cache the owning character and its animation instance
	OwningCharacter = CastChecked<ACharacter>(GetOwner());
	AnimInstance = OwningCharacter->GetMesh()->GetAnimInstance();
	
}


// Called every frame
void UCombatComponent_Base::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UCombatComponent_Base::CalculateHitDirection(FVector DamageCauserLocation, FName& Section)
{
	const FVector Forward = GetOwner()->GetActorForwardVector();

	// Lower Impact Point to the Enemy's Actor Location Z
	const FVector ImpactLowered(DamageCauserLocation.X, DamageCauserLocation.Y, GetOwner()->GetActorLocation().Z);
	const FVector ToHit = (ImpactLowered - GetOwner()->GetActorLocation()).GetSafeNormal();

	// Forward * ToHit = |Forward||ToHit| * cos(theta)
	// |Forward| = 1, |ToHit| = 1, so Forward * ToHit = cos(theta)
	const double CosTheta = FVector::DotProduct(Forward, ToHit);

	// Take the inverse cosine (arc-cosine) of cos(theta) to get theta
	double Theta = FMath::Acos(CosTheta);

	// convert from radians to degrees
	Theta = FMath::RadiansToDegrees(Theta);

	// if CrossProduct points down, Theta should be negative
	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);
	if (CrossProduct.Z < 0)
	{
		Theta *= -1.f;
	}

	Section = "FromBack";

	if (Theta >= -45.f && Theta < 45.f)
	{
		Section = FName("FromFront");
	}
	else if (Theta >= -135.f && Theta < -45.f)
	{
		Section = FName("FromLeft");
	}
	else if (Theta >= 45.f && Theta < 135.f)
	{
		Section = FName("FromRight");
	}
}

void UCombatComponent_Base::NormalDamageResponse(bool bOverrideDefaultHitResponse, UAnimMontage* OverridenDamageResponseMontage, FVector HitLocation,FVector HitImpactNormal, AActor* DamageCauser, FName HitDirectionName)
{
	if (bOverrideDefaultHitResponse)
	{

		AnimInstance->Montage_Play(OverridenDamageResponseMontage);
		AnimInstance->Montage_JumpToSection(HitDirectionName);


		// Bind montage end delegate to unlock movement
		FOnMontageEnded MontageEndDelegate;
		MontageEndDelegate.BindUObject(this, &UCombatComponent_Base::OnDamageResponseMontageEnded);
		AnimInstance->Montage_SetEndDelegate(MontageEndDelegate, OverridenDamageResponseMontage);
		return;
	}

	else
	{
		AnimInstance->Montage_Play(HitReactMontage);
		AnimInstance->Montage_JumpToSection(HitDirectionName);

		// Bind montage end delegate to unlock movement
		FOnMontageEnded MontageEndDelegate;
		MontageEndDelegate.BindUObject(this, &UCombatComponent_Base::OnDamageResponseMontageEnded);
		AnimInstance->Montage_SetEndDelegate(MontageEndDelegate, HitReactMontage);
	}



	// Play blood particle effects
	for (auto* NiagaraParticle : Niagara_Blood_Particles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraParticle, OwningCharacter->GetMesh(), FName("None"), HitLocation, FRotator::ZeroRotator, EAttachLocation::KeepWorldPosition, true);
	}
	// Play blood Decal effects
	
	if (Niagara_Blood_Decals)
	{

		UGameplayStatics::SpawnDecalAttached(Niagara_Blood_Decals, BloodDecalScale,OwningCharacter->GetMesh(),FName("None"), HitLocation,FRotationMatrix::MakeFromX(HitImpactNormal).Rotator(), EAttachLocation::KeepWorldPosition, 5.f);
	}

	// Play sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), NormalHit_Sound, HitLocation);

	return;
}

void UCombatComponent_Base::OnDamageResponseMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	
}

