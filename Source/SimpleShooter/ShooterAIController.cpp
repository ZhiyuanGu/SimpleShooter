// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"

void AShooterAIController::BeginPlay() {
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (AIBehavior) {
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	}

}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//if (PlayerPawn) {
	//	if (LineOfSightTo(PlayerPawn)) {
	//		SetFocus(PlayerPawn); // GamePlay priority
	//		MoveToActor(PlayerPawn, AcceptanceRadius); // Movement priority, follow till in 2 meters range
	//	}
	//	else {
	//		ClearFocus(EAIFocusPriority::Gameplay);
	//		StopMovement();
	//	}
	//}


}
