// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(PlayerPawn) 
    {
        SetFocus(PlayerPawn);
        //MoveToActor(PlayerPawn, 200);
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(PlayerPawn) 
    {
        MoveToActor(PlayerPawn, 200);
    }
}


