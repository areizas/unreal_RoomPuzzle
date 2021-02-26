// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_DoorKey.h"

#include "Components/StaticMeshComponent.h"

ARP_DoorKey::ARP_DoorKey()
{
	KeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	KeyMeshComponent->SetupAttachment(MainColliderComponent);
	KeyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	KeyTag = "KeyA";
}

void ARP_DoorKey::PickUp(ARP_Character* PickUpCharacter)
{
	Super::PickUp(PickUpCharacter);
	PickUpCharacter->AddKey(KeyTag);
	Destroy();
}
