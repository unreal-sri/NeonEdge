#pragma once

UENUM(BlueprintType)
enum class ECharacterStance : uint8
{
	ECS_Unarmed UMETA(DisplayName = "Unarmed"),
	ECS_Gun UMETA(DisplayName = "Gun"),
	ECS_Melee UMETA(DisplayName = "Melee"),
	ECS_Block UMETA(DisplayName = "Block"),
	ECS_Crouch UMETA(DisplayName = "Crouch")
};

UENUM(BlueprintType)
enum class EGait : uint8
{
	EG_Walk UMETA(DisplayName = "Walk"),
	EG_Jog UMETA(DisplayName = "Jog"),
	EG_Sprint UMETA(DisplayName = "Sprint")
};

UENUM(BlueprintType)
enum class EHitType : uint8
{
	EHT_None UMETA(DisplayName = "None"),
	EHT_Slashed UMETA(DisplayName = "Slashed"),
	EHT_Parried UMETA(DisplayName = "Parried"),
	EHT_Blocked UMETA(DisplayName = "Blocked"),
	EHT_BulletHit UMETA(DisplayName = "BulletHit")
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	EAT_Light UMETA(DisplayName = "Light"),
	EAT_Heavy UMETA(DisplayName = "Heavy"),
	EAT_Special UMETA(DisplayName = "Special")
};

UENUM(BlueprintType)
enum class EDamageResponse : uint8
{
	EDR_None UMETA(DisplayName = "None"),
	EDR_NormalHit UMETA(DisplayName = "NormalHit"),
	EDR_NormalHit2 UMETA(DisplayName = "NormalHit2"),
	EDR_HeavyHit UMETA(DisplayName = "HeavyHit"),
	EDR_LaunchHit UMETA(DisplayName = "LaunchHit")
};

UENUM(BlueprintType)
enum class EAIStates : uint8
{
	EAIS_Passive UMETA(DisplayName = "Passive"),
	EAIS_Attacking UMETA(DisplayName = "Attacking"),
	EAIS_Frozen UMETA(DisplayName = "Frozen"),
	EAIS_Investigating UMETA(DisplayName = "Investigating"),
	EAIS_Dead UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class EPlayerStates : uint8
{
	EPS_Passive UMETA(DisplayName = "Passive"),
	EPS_Attack UMETA(DisplayName = "Attack"),
	EPS_Frozen UMETA(DisplayName = "Frozen"),
	EPS_Dodge UMETA(DisplayName = "Dodge"),
	EPS_Dead UMETA(DisplayName = "Dead")
};

// AI Senses 

UENUM(BlueprintType)
enum class EAISenses : uint8
{
	EAIS_None UMETA(DisplayName = "None"),
	EAIS_Sight UMETA(DisplayName = "Sight"),
	EAIS_Hearing UMETA(DisplayName = "Hearing"),
	EAIS_Damage UMETA(DisplayName = "Damage")
};

UENUM(BlueprintType)
enum class ECameraManagerState : uint8
{
	ECMS_Idle UMETA(DisplayName = "UnarmedIdle"),
	ECMS_Walk UMETA(DisplayName = "UnarmedWalk"),
	ECMS_Jog UMETA(DisplayName = "UnarmedJogging")
};