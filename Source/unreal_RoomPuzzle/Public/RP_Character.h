// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "RP_Character.generated.h"

class UCameraComponent;

UCLASS()
class UNREAL_ROOMPUZZLE_API ARP_Character : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component")
	UCameraComponent* FPSCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component")
    UCameraComponent* TPSCameraComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Aiming")
	bool bUseFirstPersonView;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Aiming")
	bool bIsLookInversion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Aiming")
	bool bIsSlowSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Aiming")
	FName FPSCameraSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement")
	float MaxSpeedRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement")
	float MinSpeedRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Key")
	TArray<FName> DoorKeys;

	
	
public:
	// Sets default values for this character's properties
	ARP_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	virtual void AddControllerPitchInput(float Value) override;

	virtual void Jump() override;
	virtual void StopJumping() override;

	void Run();
	void StopRunning();

	void LowSpeed();
	void StopLowSpeed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddKey(FName NewKey);

	bool HasKey(FName KeyTag);
};
