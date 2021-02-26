// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_Platform.h"

#include <openexr/Deploy/include/ImathMath.h>


#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

class USceneComponent;
// Sets default values
ARP_Platform::ARP_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;
	
	PlatformMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMeshComponent->SetupAttachment(CustomRootComponent);

	Speed = 5.0f;
	MaxHeight = 200.0f;
	MinHeight = 10.0f;
	bIsGoingUp = true;
	bMoveOnZDirection = true;
	bMoveOnXDirection = false;
	bMoveOnYDirection = false;
}

// Called when the game starts or when spawned
void ARP_Platform::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARP_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ARP_Platform::Move()
{
	FVector UPDirection;

	if (bMoveOnZDirection)
	{
		UPDirection = UKismetMathLibrary::GetUpVector(GetActorRotation());
		if((GetActorLocation().Z >= MaxHeight && bIsGoingUp) || (GetActorLocation().Z<=MinHeight && !bIsGoingUp))
		{
			bIsGoingUp = !bIsGoingUp;
		}
	} else if(bMoveOnXDirection)
	{
		UPDirection = UKismetMathLibrary::GetForwardVector(GetActorRotation());
		if((GetActorLocation().X >= MaxHeight && bIsGoingUp) || (GetActorLocation().X<=MinHeight && !bIsGoingUp))
		{
			bIsGoingUp = !bIsGoingUp;
		}
	} else
	{
		UPDirection = UKismetMathLibrary::GetRightVector(GetActorRotation());
		if((GetActorLocation().Y >= MaxHeight && bIsGoingUp) || (GetActorLocation().Y<=MinHeight && !bIsGoingUp))
		{
			bIsGoingUp = !bIsGoingUp;
		}
	}

	if(!bIsGoingUp)
	{
		UPDirection = UPDirection * -1;
	}
	
	FVector CurrentVelocity = UPDirection * Speed;
	FVector NewLocation = GetActorLocation() + CurrentVelocity;
	SetActorLocation(NewLocation);
}
