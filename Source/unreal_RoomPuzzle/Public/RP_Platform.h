// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RP_Platform.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class UNREAL_ROOMPUZZLE_API ARP_Platform : public AActor
{
	GENERATED_BODY()

//Components section
protected:

	UPROPERTY(VisibleAnywhere, Category="Components")
	USceneComponent* CustomRootComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* PlatformMeshComponent;

//Variable section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Platform")
	bool bIsGoingUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Platform")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Platform")
	float MinHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Platform")
	float MaxHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Platform")
	bool bMoveOnZDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Platform")
	bool bMoveOnXDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Platform")
	bool bMoveOnYDirection;
	
//Constructor section
public:	
	// Sets default values for this actor's properties
	ARP_Platform();

//Function section
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable,Category="Movement")
	void Move();
	
//Function section
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
