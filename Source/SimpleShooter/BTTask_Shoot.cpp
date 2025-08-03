// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "ShooterCharacter.h"
#include "AIController.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AShooterCharacter* AIPwn = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if(!OwnerComp.GetAIOwner() or !AIPwn) return EBTNodeResult::Failure;
    AIPwn->Shoot();

    return EBTNodeResult::Succeeded;
}
