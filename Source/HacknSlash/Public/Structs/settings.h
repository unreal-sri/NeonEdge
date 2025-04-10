#pragma once
#include "CoreMinimal.h"
#include "Enums/States.h"
#include "Settings.generated.h"



USTRUCT(BlueprintType)
struct FActorStats
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float Balance;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float MaxBalance;
};


USTRUCT(BlueprintType)
struct FStatusEffects
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float Burn;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float Freeze;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float Soak;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float Blind;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float Poison;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float Shock;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float Dizz;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float Knock;

};

USTRUCT(BlueprintType)
struct FMaxStatusEffects
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float MaxBurn;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float MaxFreeze;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float MaxSoak;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float MaxBlind;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float MaxPoison;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float MaxShock;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float MaxDizz;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	float MaxKnock;
};

USTRUCT(BlueprintType)
struct FActorStatsScale
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	int SwordPower;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	int GunPower;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	int Health;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes", BlueprintReadWrite)
	int Balance;
};

USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	float HealthDamage;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	float BalanceDamage;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	bool bCanBeDodged;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	bool bOverrideDefaultHitResponse;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	UAnimMontage* OverridenDamageResponseMontage;

	UPROPERTY(VisibleAnywhere, Category = "DamageInfo", BlueprintReadOnly)
	FVector HitLocation;

	UPROPERTY(VisibleAnywhere, Category = "DamageInfo", BlueprintReadOnly)
	FName HitBoneName;

	UPROPERTY(VisibleAnywhere, Category = "DamageInfo", BlueprintReadOnly)
	FVector HitImpactNormal;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	float LaunchSpeed;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	EDamageResponse ResponseType;

	UPROPERTY(EditAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	EAttackType AttackType;

	UPROPERTY(VisibleAnywhere, Category = "DamageInfo", BlueprintReadWrite)
	AActor* DamageCauser;
};

USTRUCT(BlueprintType)
struct FAttackInfo
{
	GENERATED_BODY()

public:

	FName AttackName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TokensRequired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AttackMontage;

	UPROPERTY(Transient)
	AActor* AttackTarget; //Will Be set In game logic
};

USTRUCT(BlueprintType)
struct FAttackResult
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	bool bSuccess = false;

	UPROPERTY(VisibleAnywhere)
	bool bGotBlocked = false;

	UPROPERTY(VisibleAnywhere)
	bool bGotParried = false;

	UPROPERTY(VisibleAnywhere)
	bool bGotDodged = false;
};

USTRUCT(BlueprintType)
struct FCameraManagerSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float CamDistanceOffset_Up;

	UPROPERTY(EditAnywhere)
	float CamDistanceOffset_Forward;

	UPROPERTY(EditAnywhere)
	float CamDistanceOffset_Right;

	UPROPERTY(EditAnywhere)
	float LerpRate;

	UPROPERTY(EditAnywhere)
	bool bUseCurve;

	UPROPERTY(EditAnywhere)
	UCurveFloat* Curve;
};

USTRUCT(BlueprintType)
struct FCameraManagerStatesSettings
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Settings", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FCameraManagerSettings IdleStateSettings;

	UPROPERTY(EditAnywhere, Category = "Settings", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FCameraManagerSettings WalkStateSettings;

	UPROPERTY(EditAnywhere, Category = "Settings", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FCameraManagerSettings JogStateSettings;
};


USTRUCT(BlueprintType)
struct FMotionWarpingDetails
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = "MotionWarping", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* ActorToOffsetFrom;

	UPROPERTY(EditAnywhere, Category = "MotionWarping", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName WarpTargetName;

	UPROPERTY(VisibleAnywhere, Category = "MotionWarping", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UMotionWarpingComponent* MotionWarpingComponent;

	UPROPERTY(EditAnywhere, Category = "MotionWarping", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector LocationOffset;

	UPROPERTY(EditAnywhere, Category = "MotionWarping", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FRotator RotationOffset;
};

