// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
    if (LoseScreen != nullptr)
    {
        LoseScreen -> AddToViewport();
    }

    UE_LOG(LogTemp, Warning, TEXT("You lost!"));
    GetWorldTimerManager().SetTimer(RestartTimer, this, &AMyPlayerController::RestartLevel, RestartDelay);
}
