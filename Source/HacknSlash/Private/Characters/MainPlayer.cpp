// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainPlayer.h"

//Components
#include "Components/InputComponent.h"																												  
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MotionWarpingComponent.h"
//CustomComp
#include "ActorComponents/CombatComponent_Player.h"
// otherclasses 
#include "Weapons/Weapon_Melee.h"

//System
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayMontageCallbackProxy.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CombatComponent = CreateDefaultSubobject<UCombatComponent_Player>(TEXT("CombatComponent"));

}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (auto* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Player, 0);
		}
	}
	
}

UCombatComponent_Player* AMainPlayer::GetPlayerCombatComponent()
{
	return CombatComponent;
}

AWeapon_Melee* AMainPlayer::GetMeleeWeapon()
{
	return MeleeWeapon;
}

EPlayerStates AMainPlayer::GetCurrentState()
{
	return CurrentState;
}

void AMainPlayer::SetCurrentState(EPlayerStates State)
{
	CurrentState = State;
}


// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	 auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		//Movements
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMainPlayer::ActionLook);
		//EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Completed, this, &AMainPlayer::CanSwitch);
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMainPlayer::ActionMove);

		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &AMainPlayer::ActionJump);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AMainPlayer::ActionStopJump);

		// CombatActions
	
		EnhancedInputComponent->BindAction(IA_LightAttack, ETriggerEvent::Triggered, this, &AMainPlayer::ActionLightAttack);
		EnhancedInputComponent->BindAction(IA_HeavyAttack, ETriggerEvent::Triggered, this, &AMainPlayer::ActionHeavyAttack);
		EnhancedInputComponent->BindAction(IA_Dodge, ETriggerEvent::Started, this, &AMainPlayer::ActionDodge);
		//EnhancedInputComponent->BindAction(IA_AltAction, ETriggerEvent::Completed, this, &AMainPlayer::ActionAltActionEnd);*/

		//Extras
		/*EnhancedInputComponent->BindAction(IA_StanceAbility, ETriggerEvent::Triggered, this, &AMainPlayer::ActionStanceAbility);
		EnhancedInputComponent->BindAction(IA_StanceAbility, ETriggerEvent::Completed, this, &AMainPlayer::StopStanceAbility);*/
	}

}


void AMainPlayer::ActionLook(const FInputActionValue& Value)
{
	FVector2D LookingVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("Looking: %f"), LookingVector.X);

		if (GetController())
		{
			AddControllerYawInput(LookingVector.X * BaseTurnRate * GetWorld()->GetDeltaSeconds());
			AddControllerPitchInput(LookingVector.Y * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
		}
}


void AMainPlayer::ActionMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	float MoveInputValue = Value.Get<float>();

		FRotator Rotation = GetController()->GetControlRotation();
		FRotator YawRotation = { 0.0f,Rotation.Yaw,0.0f };

		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);


	
}

void AMainPlayer::ActionJump(const FInputActionValue& Value)
{
	if (GetCurrentState() == EPlayerStates::EPS_Passive)
	{
		Jump();

	}
	else
	{
		StopJumping();
	}
}

void AMainPlayer::ActionStopJump(const FInputActionValue& Value)
{
	StopJumping();
}

void AMainPlayer::ActionLightAttack(const FInputActionValue& Value)
{

}

void AMainPlayer::ActionHeavyAttack(const FInputActionValue& Value)
{
}

void AMainPlayer::ActionDodge(const FInputActionValue& Value)
{
	if (GetCurrentState() == EPlayerStates::EPS_Dodge || GetCurrentState() == EPlayerStates::EPS_Attack)
	{
		CombatComponent->bContinueDodge = true;
	}

	else
	{
		if (CombatComponent->CanDodge())
		{
			//Clear Attack Variables
			CombatComponent->bSwitchHeavyCombo = false;
			CombatComponent->bSwitchLightCombo = false;
			CombatComponent->LightAttackIndex = 0;
			CombatComponent->HeavyAttackIndex = 0;

			//DodgeDirection
			FRotator Rotator =  FRotationMatrix::MakeFromX(GetCharacterMovement()->GetLastInputVector()).Rotator();

			FRotator Rot = GetCharacterMovement()->GetLastInputVector() != FVector(0.f) ? Rotator : FRotator(0.f);

			if (Rot != FRotator(0.f))
			{
				SetActorRotation(Rot);
				CombatComponent->PerformDodge(DodgeMontage);
			}
			else if (Rot == FRotator(0.f))
			{
				CombatComponent->PerformDodge(DodgeMontage);
			}
		}
	}

}

