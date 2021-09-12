// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"


UBTTask_Shoot::UBTTask_Shoot() {
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// nullptr check is in general good practice
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Type::Failed;
	}

	AShooterCharacter* OwnerShooter = Cast<AShooterCharacter>(AIController->GetPawn());
	if (!OwnerShooter)
	{
		return EBTNodeResult::Type::Failed;
	}

	OwnerShooter->Shoot();

	return EBTNodeResult::Type::Succeeded;
}
