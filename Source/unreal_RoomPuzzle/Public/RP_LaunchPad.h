// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"

#include "RP_LaunchPad.generated.h"

UCLASS()
class UNREAL_ROOMPUZZLE_API ARP_LaunchPad : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* CustomRootComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* LaunchPadComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBoxComponent* KeysZoneColliderComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* SpringArmComponent;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LaunchPad")
	FName LaunchPadTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LaunchPad")
	float OpenAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LaunchPad")
	int PayerLaunchXYVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LaunchPad")
	int PayerLaunchZVelocity;
	
public:	
	// Sets default values for this actor's properties
	ARP_LaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Launch();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category="LaunchPad")
	void BP_Launch();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category="LaunchPad")
    void BP_MoveLaunchPad();

	UFUNCTION()
    void CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
