// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PenguinAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_KINGS_API UPenguinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	public:
		virtual void NativeInitializeAnimation() override;
		virtual void NativeUpdateAnimation(float DeltaTime) override;
	private:
		UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
		class APenguin* PenguinCharacter;

		UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool isRunning;
};
