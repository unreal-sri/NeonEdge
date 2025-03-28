// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"

#include "Weapon_Melee.generated.h"


class UStaticMeshComponent;
class UBoxComponent;
class UActorComp_Item;
class UMnhTracerComponent;
class UMnhBoxComponent;

UCLASS()
class HACKNSLASH_API AWeapon_Melee : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Melee();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Miss no hit 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags", meta = (AllowPrivateAccess = "true"))
	FGameplayTagContainer TracerTags;

	//Components

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;


	//Miss no hit
	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMnhTracerComponent* TraceComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMnhBoxComponent* MnhBoxComp;


public:
	FORCEINLINE UMnhTracerComponent* GetTracerComponent() { return TraceComponent;}


	UFUNCTION(BlueprintPure)
	FORCEINLINE UStaticMeshComponent* GetMesh() { return Mesh; };
};
