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
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	FHitResult HitResult;
	FVector InShotDirection;
	bool bSuccess = GunTrace(HitResult, InShotDirection);
	if (bSuccess) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitResult.Location, InShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, HitResult.Location);
		// cause damage
		AActor* ActorOnHit = HitResult.GetActor();
		if (ActorOnHit) {
			FPointDamageEvent DamageEvent(Damage, HitResult, InShotDirection, nullptr);
			ActorOnHit->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
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

bool AGun::GunTrace(FHitResult& HitResult, FVector& InShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) {
		return false;
	}
	FVector ControllerLocation;
	FRotator ControllerRotation;
	OwnerController->GetPlayerViewPoint(ControllerLocation, ControllerRotation);
	InShotDirection = -ControllerRotation.Vector();
	FVector End = ControllerLocation + ControllerRotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(HitResult, ControllerLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) {
		return nullptr;
	}
	return OwnerPawn->GetController();

}

