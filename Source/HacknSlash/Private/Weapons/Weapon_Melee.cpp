// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon_Melee.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "MissNoHit/Public/MnhTracerComponent.h"
#include "MissNoHit/Public/MnhComponents.h"

// Sets default values
AWeapon_Melee::AWeapon_Melee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(GetRootComponent());

	// MissNoHit Collision Box
	MnhBoxComp = CreateDefaultSubobject<UMnhBoxComponent>(TEXT("MnhBox"));
	MnhBoxComp->SetupAttachment(Mesh);

	//miss no hit tracer component
	TraceComponent = CreateDefaultSubobject<UMnhTracerComponent>(TEXT("TraceComponent"));
	TracerTags = FGameplayTagContainer(FGameplayTag::RequestGameplayTag("R_PrimaryWeapon"));

}

// Called when the game starts or when spawned
void AWeapon_Melee::BeginPlay()
{
	Super::BeginPlay();
	if (!TracerTags.IsEmpty())
	{
		TraceComponent->InitializeTracers(TracerTags, MnhBoxComp);
	}
	
}

// Called every frame
void AWeapon_Melee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

