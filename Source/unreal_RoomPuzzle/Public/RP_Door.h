// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RP_Door.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class UNREAL_ROOMPUZZLE_API ARP_Door : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARP_Door();

	UPROPERTY(VisibleAnyWhere,Category = "Components")
	USceneComponent* CustomRootComponent;
	
	UPROPERTY(VisibleAnyWhere, Category = "Components")
	UStaticMeshComponent* DoorFrameComponent;
	
	UPROPERTY(VisibleAnyWhere, Category = "Components")
	UStaticMeshComponent* DoorComponent;

	UPROPERTY(EditAnywhere, Category = "My Door")
	float OpenAngle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OpenDoor();
};
