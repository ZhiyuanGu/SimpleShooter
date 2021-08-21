// Fill out your copyright notice in the Description page of Project Settings.
#include "Gun.h"

#include"Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	//UE_LOG(LogTemp, Warning, TEXT("Trigger pulled"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) {
		return;
	}
	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) {
		return;
	}
	FVector ControllerLocation;
	FRotator ControllerRotation;
	OwnerController->GetPlayerViewPoint(ControllerLocation, ControllerRotation);
	FVector End = ControllerLocation + ControllerRotation.Vector() * MaxRange;
	FHitResult HitResult;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, ControllerLocation, End, ECollisionChannel::ECC_GameTraceChannel1);
	if (bSuccess) {
		// DrawDebugPoint(GetWorld(), HitResult.Location, 20.0f, FColor::Red, true);
		FVector InShotDirection = -ControllerRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitResult.Location, InShotDirection.Rotation());
		// cause damage
		AActor* ActorOnHit = HitResult.GetActor();
		if (ActorOnHit) {
			FPointDamageEvent DamageEvent(Damage, HitResult, InShotDirection, nullptr);
			ActorOnHit->TakeDamage(Damage, DamageEvent, OwnerController, OwnerPawn);
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

