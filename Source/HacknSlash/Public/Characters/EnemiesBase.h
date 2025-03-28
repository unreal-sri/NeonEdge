// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Interfaces/InterfaceCharacter.h>
#include "EnemiesBase.generated.h"

class UMotionWarpingComponent;
class UCombatComponent_Enemy;
class UCombatComponent_Base;

UCLASS()
class HACKNSLASH_API AEnemiesBase : public ACharacter , public IInterfaceCharacter 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemiesBase();



private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCombatComponent_Enemy* CombatComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviourTree;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UCombatComponent_Base* GetCombatComponent() override;
	virtual UBehaviorTree* GetBehaviorTree() override;
	FORCEINLINE virtual UCombatComponent_Enemy* GetEnemyCombatComponent() override { return CombatComponent; };



};
