// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay() {
	Super::BeginPlay();

}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn) {
		if (LineOfSightTo(PlayerPawn)) {
			SetFocus(PlayerPawn); // GamePlay priority
			MoveToActor(PlayerPawn, AcceptanceRadius); // Movement priority, follow till in 2 meters range
		}
		else {
			ClearFocus(EAIFocusPriority::Gameplay);
			StopMovement();
		}
	}

}
