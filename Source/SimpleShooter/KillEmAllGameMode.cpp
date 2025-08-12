// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "GameFramework/Controller.h"
void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    UE_LOG(LogTemp, Display, TEXT("A Pawn was killed!"));
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController)
    {
        EndGame(false);
    }
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for(AController* Controller : TActorRange<AController>(GetWorld()))     // iterating over actors in the world to check if the player is dead
    {
        // if((Controller -> IsPlayerController() and bIsPlayerWinner) or      //  if found actor is the player and if the player is not dead
        // (!Controller -> IsPlayerController() and !bIsPlayerWinner))         //  if found actor is not a player and if the player is dead
        // {
        //     Controller->GameHasEnded(nullptr, true);
        // }
        // else
        // {
        //     Controller->GameHasEnded(nullptr, false);
        // }
        Controller -> GameHasEnded(
            Controller->GetPawn(),
            Controller -> IsPlayerController() == bIsPlayerWinner
        );
    }
}
