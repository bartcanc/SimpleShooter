// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("You've beed shot!"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if(!PawnOwner or !PawnOwner->GetController()) return;
	FVector LocationC;
	FRotator RotationC;
	PawnOwner -> GetController() -> GetPlayerViewPoint(LocationC, RotationC);

	FVector End = LocationC + RotationC.Vector() * MaxRange;

	//DrawDebugPoint(GetWorld(), End, 10, FColor::Red, true);
	FHitResult Hit;
	bool bSuccess = GetWorld() -> LineTraceSingleByChannel(Hit, LocationC, End, ECollisionChannel::ECC_GameTraceChannel1);

	if(bSuccess) 
	{
		// mine
		//UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFlash, Hit.Location, FRotator::ZeroRotator, true);
		
		// udemy
		FVector ShotDirection = -RotationC.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFlash, Hit.Location, ShotDirection.Rotation(), true);
		//DrawDebugPoint(GetWorld(), Hit.Location, 10, FColor::Red, true);
	}
}
// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

