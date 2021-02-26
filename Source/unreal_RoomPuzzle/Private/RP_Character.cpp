// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_Character.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARP_Character::ARP_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxSpeedRate = 1.5f;
	MinSpeedRate = 0.5f;

	bIsSlowSpeed = false;

	bUseFirstPersonView = true;
	FPSCameraSocketName = "SCK_Camera";
	
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_CamperaComponent"));
	FPSCameraComponent->bUsePawnControlRotation = true;
	FPSCameraComponent->SetupAttachment(GetMesh(),FPSCameraSocketName);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);
	
	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_CamperaComponent"));
	TPSCameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ARP_Character::BeginPlay()
{
	Super::BeginPlay();
}

void ARP_Character::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void ARP_Character::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void ARP_Character::AddControllerPitchInput(float Value)
{
	Super::AddControllerPitchInput(bIsLookInversion ? -Value : Value);
}

void ARP_Character::Jump()
{
	Super::Jump();
}

void ARP_Character::StopJumping()
{
	Super::StopJumping();
}

void ARP_Character::Run()
{
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->GetMaxSpeed()*MaxSpeedRate;
}

void ARP_Character::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->GetMaxSpeed()/MaxSpeedRate;
}

void ARP_Character::LowSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->GetMaxSpeed()*MinSpeedRate;
	bIsSlowSpeed = true;
}

void ARP_Character::StopLowSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->GetMaxSpeed()/MinSpeedRate;
	bIsSlowSpeed = false;
}

// Called every frame
void ARP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARP_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this, &ARP_Character::MoveRight);

	PlayerInputComponent->BindAxis("LookUP",this,&ARP_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight",this,&ACharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ARP_Character::Jump);
	PlayerInputComponent->BindAction("StopJumping",IE_Released,this,&ARP_Character::StopJumping);

	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&ARP_Character::Run);
	PlayerInputComponent->BindAction("StopRunning",IE_Released,this,&ARP_Character::StopRunning);

	PlayerInputComponent->BindAction("LowSpeed",IE_Pressed,this,&ARP_Character::LowSpeed);
	PlayerInputComponent->BindAction("StopLowSpeed",IE_Released,this,&ARP_Character::StopLowSpeed);
}

void ARP_Character::AddKey(FName NewKey)
{
	DoorKeys.Add(NewKey);
}

bool ARP_Character::HasKey(FName KeyTag)
{
	return DoorKeys.Contains(KeyTag);
}

