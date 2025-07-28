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
        // GetBlackboardComponent() -> SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(LineOfSightTo(PlayerPawn)) 
    {
        GetBlackboardComponent() -> SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent() -> SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    }
    else
    {
       GetBlackboardComponent() -> ClearValue(TEXT("PlayerLocation"));
    }
}


