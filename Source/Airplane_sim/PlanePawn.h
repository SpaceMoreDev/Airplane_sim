// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InputAction.h"
#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlanePawn.generated.h"

/**
 * 
 */
UCLASS()
class AIRPLANE_SIM_API APlanePawn : public ABasePawn
{
	GENERATED_BODY()
	
public:
	APlanePawn();
	virtual void BeginPlay() override;

	void InputMove(const FInputActionValue& Value);
	void InputLook(const FInputActionValue& Value);

	

	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	void Turn(float Value);
	void Move(float Value);
	void VerticalMove(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UMovementComponent* MovementComponent; 

	float turn_speed = 100.0;
	float movement_speed = 500.0;
	FRotator TargetRotation;

	float ForwardVelocity = 0;

	float CameraRotationSpeed = 10.0f;
	float TargetForwardSpeed = 0;

	float verticalVelocity = 0;
};
