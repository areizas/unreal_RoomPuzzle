// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_LaunchPad.h"


#include "RP_Character.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARP_LaunchPad::ARP_LaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRootComponent"));
	RootComponent = CustomRootComponent;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(CustomRootComponent);
	
	LaunchPadComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchPadComponent"));
	LaunchPadComponent->SetupAttachment(SpringArmComponent);
	
	KeysZoneColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("KeysZoneCollider"));
	KeysZoneColliderComponent->SetupAttachment(CustomRootComponent);
	KeysZoneColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	KeysZoneColliderComponent->SetCollisionResponseToChannels(ECR_Ignore);
	KeysZoneColliderComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);

	LaunchPadTag = "KeyB";
	OpenAngle = 90.0f;
	PayerLaunchXYVelocity=-3000;
	PayerLaunchZVelocity=20;
}

// Called when the game starts or when spawned
void ARP_LaunchPad::BeginPlay()
{
	Super::BeginPlay();
	KeysZoneColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ARP_LaunchPad::CheckKeyFromPlayer);
}

// Called every frame
void ARP_LaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARP_LaunchPad::Launch()
{
	BP_Launch();
}

void ARP_LaunchPad::CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IsValid(OtherActor))
	{
		ARP_Character* OverlappedCharacter = Cast<ARP_Character>(OtherActor);
		
		if(IsValid(OverlappedCharacter))
		{
			if(! OverlappedCharacter->HasKey(LaunchPadTag))
			{
				Launch();
				const FVector ForwardDir = OverlappedCharacter->GetActorRotation().Vector();
				const FVector AddForce = ForwardDir * -3000 + FVector(0, 0, 1) * PayerLaunchZVelocity;
				OverlappedCharacter->LaunchCharacter(AddForce, false, true);
			}
		}
	}
}