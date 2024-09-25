#include "PlanePawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"

APlanePawn::APlanePawn()
{
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
    SpringArmComponent->SetupAttachment(RootComponent); 

    SpringArmComponent->TargetArmLength = 1800.0f;
    SpringArmComponent->bUsePawnControlRotation = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    Camera->SetupAttachment(SpringArmComponent);

    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

void APlanePawn::BeginPlay()
{
    Super::BeginPlay();
}

const float GravityForce = -98.0f;
FRotator MeshRotation = FRotator(0, 0, 0);

void APlanePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FRotator NewMeshRotation;
    NewMeshRotation = FMath::RInterpTo(MeshComponent->GetComponentRotation(), MeshRotation, DeltaTime, 1);

    if (FMath::Abs(ForwardVelocity) > 0)
    {
        CurrentVelocity.Z += verticalVelocity;
        
        
    }
    else
    {
        verticalVelocity = 0;

        CurrentVelocity.Z += GravityForce * DeltaTime;
        if (GetVelocity().Z != 0)
        {
            MeshRotation.Pitch = -10;
        }
        else
        {
            MeshRotation.Pitch = 0;
        }
        
    }

    AddMovementInput(CurrentVelocity * DeltaTime);

    MeshComponent->SetWorldRotation(NewMeshRotation);

    TargetRotation = MeshComponent->GetComponentRotation() + FRotator(-20, 0, 0);

    FRotator NewRotation = FMath::RInterpTo(SpringArmComponent->GetComponentRotation(), TargetRotation, DeltaTime, CameraRotationSpeed);


    UE_LOG(LogTemp, Warning, TEXT("ForwardVelocity: %f"), ForwardVelocity);


    SpringArmComponent->SetWorldRotation(NewRotation);

}

void APlanePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlanePawn::VerticalMove);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlanePawn::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlanePawn::Turn);
}

void APlanePawn::Turn(float Value)
{
    double deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    FRotator DeltaRotator = FRotator::ZeroRotator;
    MeshRotation.Yaw += Value * turn_speed * deltaTime;
}

void APlanePawn::Move(float Value)
{
    if (MovementComponent && Value != 0.0f)
    {
        CurrentVelocity = MeshComponent->GetForwardVector() * Value * 100;
    }
    ForwardVelocity = Value;
}

void APlanePawn::VerticalMove(float Value)
{
    double deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    verticalVelocity = 10* deltaTime * Value;

    if (Value > 0) 
    {
        MeshRotation.Pitch=10;
    }
    else if (Value < 0)
    {
        MeshRotation.Pitch = -10;
    }
    else
    {
        MeshRotation.Pitch = 0;
    }
}
