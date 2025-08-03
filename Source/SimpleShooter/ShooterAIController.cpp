// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    ControlledPawn = GetPawn();

    if(AIBehavior) 
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent() -> SetValueAsVector(TEXT("StartLocation"), ControlledPawn->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}


