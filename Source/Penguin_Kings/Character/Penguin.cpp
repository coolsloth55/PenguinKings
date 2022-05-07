// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/GameEngine.h"
#include "Penguin.h"

// Sets default values
APenguin::APenguin()
{
	isRunning = false;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create and spring arm Component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

	Camera->FieldOfView = 50.f;

	//Setting class variables of the Character movement component
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bIgnoreBaseRotation = true;
	GetCharacterMovement()->MaxWalkSpeed = 100.f;

	// Need to uncheck in blue print as well
	bUseControllerRotationYaw = false;

	if (GetMesh() != NULL)
	{

		//Set the location and rotation of the Character Mesh Transform
		Camera->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 120.0f), FQuat(FRotator(-20.0f, 0.0f, 0.0f)));

		// Attaching your class Components to the default character's Skeletal Mesh Component
		SpringArmComp->SetupAttachment(GetMesh());
		Camera->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

		//Setting class variables of the spring arm
		SpringArmComp->bUsePawnControlRotation = true;
		SpringArmComp->bEnableCameraLag = true;
	}
}

// Called when the game starts or when spawned
void APenguin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APenguin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APenguin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Hook up every-frame handling for our four axes
	PlayerInputComponent->BindAxis("Forward", this, &APenguin::MoveVertically);
	PlayerInputComponent->BindAxis("Back", this, &APenguin::MoveVertically);
	PlayerInputComponent->BindAxis("Right", this, &APenguin::MoveHorizontally);
	PlayerInputComponent->BindAxis("Left", this, &APenguin::MoveHorizontally);
	PlayerInputComponent->BindAxis("MouseX", this, &APenguin::Turn);
	PlayerInputComponent->BindAxis("MouseY", this, &APenguin::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APenguin::Jump);
	PlayerInputComponent->BindAction("Slide", IE_Pressed, this, &APenguin::Slide);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APenguin::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APenguin::StopSprint);
}

void APenguin::MoveVertically(float value)
{
	if (Controller != nullptr && value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, value);
	}
}

void APenguin::MoveHorizontally(float value)
{
	if (Controller != nullptr && value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, value);
	}
}

void APenguin::Jump()
{
	Super::Jump();
}

void APenguin::Turn(float value)
{
	AddControllerYawInput(value);
}

void APenguin::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void APenguin::Slide() {
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}

void APenguin::Sprint()
{
	isRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}

void APenguin::StopSprint()
{
	isRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 100.f;
}

//public functions
bool APenguin::GetIsRunning()
{
	return isRunning;
}