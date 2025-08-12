// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    if(bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if (WinScreen != nullptr)
        {
            WinScreen -> AddToViewport();
        }

        //UE_LOG(LogTemp, Warning, TEXT("You Won!"));
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if (LoseScreen != nullptr)
        {
            LoseScreen -> AddToViewport();
        }

       // UE_LOG(LogTemp, Warning, TEXT("You lost!"));
    }
    if (HUD != nullptr)
    {
        HUD -> RemoveFromViewport();
    }
    GetWorldTimerManager().SetTimer(RestartTimer, this, &AMyPlayerController::RestartLevel, RestartDelay);
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);
    if (HUD != nullptr)
    {
        HUD -> AddToViewport();
    }
}
