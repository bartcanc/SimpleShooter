// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	CurrentAmmo = MaxAmmo;
}

void AGun::PullTrigger()
{
	if(CurrentAmmo <= 0) return;
	CurrentAmmo--;
	UE_LOG(LogTemp, Display, TEXT("Ammo: %f"), CurrentAmmo);
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);
	if(bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFlash, Hit.Location, ShotDirection.Rotation(), true);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location, ShotDirection.Rotation());

		if(Hit.GetActor())
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			Hit.GetActor() -> TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
			UE_LOG(LogTemp, Warning, TEXT("You've been shot!"));
		} 
	}
}

void AGun::Reload()
{
	if(CurrentAmmo < MaxAmmo) CurrentAmmo = MaxAmmo;
}

float AGun::GetCurrentAmmo() const
{
	return CurrentAmmo;
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

bool AGun::GunTrace(FHitResult &Hit, FVector &ShotDirection)
{
	FVector ShotLocation;
	FRotator ShotRotation;
	GetOwnerController() -> GetPlayerViewPoint(ShotLocation, ShotRotation);

	ShotDirection = -ShotRotation.Vector();

	FVector End = ShotLocation + ShotRotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	ShotDirection = -ShotRotation.Vector();
	return GetWorld() -> LineTraceSingleByChannel(Hit, ShotLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if(!PawnOwner) return nullptr;
	return PawnOwner->GetController();
}
