// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\RP_Door.h"

#include "RP_Character.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARP_Door::ARP_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomComponent"));
	RootComponent = CustomRootComponent;

	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrameComponent->SetupAttachment(CustomRootComponent);

	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorComponent->SetupAttachment(CustomRootComponent);

	KeysZoneColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("KeysZoneCollider"));
	KeysZoneColliderComponent->SetupAttachment(CustomRootComponent);
	KeysZoneColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	KeysZoneColliderComponent->SetCollisionResponseToChannels(ECR_Ignore);
	KeysZoneColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	DoorTag = "KeyA";
	bIsOpen = false;
	OpenAngle = -90.0f;
}

// Called when the game starts or when spawned
void ARP_Door::BeginPlay()
{
	Super::BeginPlay();
	KeysZoneColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ARP_Door::CheckKeyFromPlayer);
}

// Called every frame
void ARP_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARP_Door::OpenDoor()
{
	//FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
	//DoorComponent->SetRelativeRotation(NewRotation);
	bIsOpen = true;
	BP_OpenDoor();
}

void ARP_Door::CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(bIsOpen)
	{
		return;
	}
	
	if(IsValid(OtherActor))
	{
		ARP_Character* OverlappedCharacter = Cast<ARP_Character>(OtherActor);

		if(IsValid(OverlappedCharacter))
		{
			if(OverlappedCharacter->HasKey(DoorTag))
			{
				OpenDoor();
			}
		}
	}
}