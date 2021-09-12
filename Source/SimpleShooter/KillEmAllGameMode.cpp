// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled) {
	Super::PawnKilled(PawnKilled);
	UE_LOG(LogTemp, Warning, TEXT("Pawn was killed"));
	// check if game is over
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController) {
		EndGame(false);
	}
	// loop over ShooterAI in World to check Player Win condition
	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld())) {
		if (!Controller->IsDead()) {
			return;
		}
	}
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bPlayerWon)
{
	for (AController* Controller : TActorRange<AController>(GetWorld())) {
		Controller->GameHasEnded(Controller->GetPawn(), bPlayerWon == Controller->IsPlayerController());
	}
}
