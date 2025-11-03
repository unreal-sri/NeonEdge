// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/States.h"

#include "InterfaceController.generated.h"

// This class does not need to be modified.

class UBrainComponent;

UINTERFACE(MinimalAPI)
class UInterfaceController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HACKNSLASH_API IInterfaceController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual EAIStates GetAIState() { return EAIStates(); };
	virtual void SetStateAsPassive() {};
	virtual void SetStateAsAttacking() {};
	virtual void SetStateAsFrozen() {};
	virtual void SetStateAsDead() {};
	virtual void SetStateAsBlocking() {};
	virtual void SetStateAsInvestigating(FVector Location) {};
	virtual void SetIsGettingHit(bool bIsGettingHit) {};

	FORCEINLINE virtual UBrainComponent* GetBrainComp() { return nullptr; };
};
