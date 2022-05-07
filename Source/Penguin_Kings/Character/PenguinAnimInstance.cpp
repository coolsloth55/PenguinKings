// Fill out your copyright notice in the Description page of Project Settings.


#include "PenguinAnimInstance.h"
#include "Penguin.h"

void UPenguinAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	PenguinCharacter = Cast<APenguin>(TryGetPawnOwner());
}

void UPenguinAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (PenguinCharacter == nullptr)
	{
		PenguinCharacter = Cast<APenguin>(TryGetPawnOwner());
	}
	if (PenguinCharacter == nullptr) return;


	isRunning = PenguinCharacter->GetIsRunning();
}

