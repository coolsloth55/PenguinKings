// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Penguin.generated.h"

UCLASS()
class PENGUIN_KINGS_API APenguin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APenguin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Spring Arm Component to follow the camera behind the player
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComp;

	// Main pawn camera
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	//Movement functions
	void MoveVertically(float value);
	void MoveHorizontally(float value);
	void Turn(float value);
	void LookUp(float value);

	//Action functions
	virtual void Jump() override;
	void Slide();
	void Sprint();
	void StopSprint();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
