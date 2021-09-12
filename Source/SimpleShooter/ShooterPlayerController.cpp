// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner) {
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UE_LOG(LogTemp, Warning, TEXT("Game has ended!"));
	if (bIsWinner) {
		// Win screen
		GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
		UUserWidget* LoseScreen = CreateWidget(this, WinScreenClass);
		if (LoseScreen) {
			LoseScreen->AddToViewport();
		}
	}
	else {
		// lose screen
		GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen) {
			LoseScreen->AddToViewport();
		}
	}
}