// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMovementComponent.h"
#include "GP3Team3/Player/PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GP3Team3/Enemy/BaseEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	bUseAccelerationForPaths = true;
	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetPawnOwner();
	Capsule = Cast<UCapsuleComponent>(Owner->GetComponentByClass(UCapsuleComponent::StaticClass()));
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector& Vel = Velocity;

	FVector Input = ConsumeInputVector();
	CalculateNextVelocity(Vel, Input, DeltaTime);

	bool bPreviousOnGround = bOnGround;

	ExecuteMovement(Vel, bOnGround, DeltaTime);

	if (bPreviousOnGround != bOnGround)
	{
		OnGroundStateChanged.Broadcast(bOnGround, bPreviousOnGround);
	}

	if (bOnGround && Vel.Z < 0)
		Vel.Z = 0;
}

FMovementStatics UPlayerMovementComponent::CreateFrameMovement() const
{
	return FMovementStatics(UpdatedComponent);
}

void UPlayerMovementComponent::Move(FMovementStatics& FrameMovement)
{
	FHitResult Hit;
	if (FrameMovement.ShouldApplyGravity())
	{
		SafeMoveUpdatedComponent(FrameMovement.GetGravity(), UpdatedComponent->GetComponentQuat(), true, Hit);
		Hit.Reset();
	}

	FVector Delta = GetMovementDelta(FrameMovement);

	if (!Delta.IsNearlyZero())
	{
		SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentQuat(), true, Hit);

		SlideAlongSurface(Delta, 1.0f - Hit.Time, Hit.Normal, Hit);
	}

	FrameMovement.Hit = Hit;
	FrameMovement.FinalLocation = UpdatedComponent->GetComponentLocation();
}

bool UPlayerMovementComponent::GetSurfaceNormal(FVector& OutNormal)
{
	if (!bOnGround)
		return false;

	FVector Normal = GroundNormal.GetSafeNormal();

	bool bIsValid = Normal.IsNormalized();

	if (bIsValid)
	{
		OutNormal = Normal;
	}

	return bIsValid;
}

UMovementData* UPlayerMovementComponent::GetMovementData()
{
	return MovementData;
}

void UPlayerMovementComponent::CalculateNextVelocity(FVector& TargetVelocity, const FVector& Input, float DeltaTime)
{
	if (!MovementData || !Owner)
		return;

	float FrameMoveSpeed = MovementData->MoveSpeed;
	float FrameAcceleration = MovementData->Acceleration;
	float FrameGravity = MovementData->Gravity;

	FVector InputVector = Input;
	InputVector = FVector(InputVector.X, InputVector.Y, 0);
	MoveAxes = InputVector * FrameMoveSpeed;

	FVector Fwd = FVector::ForwardVector * MoveAxes.X;
	FVector Rgt = FVector::RightVector * MoveAxes.Y;
	FVector NextVelocity = FMath::VInterpConstantTo(TargetVelocity, (Fwd + Rgt), DeltaTime, FrameAcceleration * FrameAcceleration * DeltaTime);
	
	const float VelZ = TargetVelocity.Z;
	TargetVelocity.Z = VelZ - FrameGravity * DeltaTime;
	TargetVelocity = UKismetMathLibrary::VInterpTo_Constant(FVector(TargetVelocity.X, TargetVelocity.Y, 0), NextVelocity, DeltaTime, FrameAcceleration * FrameAcceleration * 0.4f * DeltaTime);
	TargetVelocity = FVector(NextVelocity.X, NextVelocity.Y, TargetVelocity.Z).GetSafeNormal();
}

FVector UPlayerMovementComponent::GetMovementDelta(const FMovementStatics& FrameMovement) const
{
	return FrameMovement.GetMovementDelta();
}

void UPlayerMovementComponent::ExecuteMovement(FVector& TestVelocity, bool& bTestOnGround, float DeltaTime)
{
	
	if (!MovementData)
		return;

	if (!Capsule)
		return;
	
	if (!Owner)
	{
		return;
	}
	
	FHitResult Hit;
	FHitResult ZHit;
	
	// Is applied at the end of the function to &TestOnGround
	bool bDidTouchGround = false;
	
	FVector Translation;
	bool bApplyToTestSpeed = false;

#pragma region Vertical
	
	// The vertical movement this frame.
	FVector ZTranslation;
	if (bTestOnGround)
	{
		// When on ground, we want to add some downwards velocity so we can sweep
		// to check if we have ground beneath us. Of course, since this invalidates
		// jumping, we only do this if our velocity is less than or equal to 0.
		if (TestVelocity.Z > 0)
			ZTranslation = FVector(0,0, TestVelocity.Z);
		else
			ZTranslation = FVector::DownVector * MovementData->Gravity;
	}
	else
	{
		ZTranslation = FVector(0,0, TestVelocity.Z);
	}

	ZTranslation = FVector::DownVector * MovementData->Gravity;
	Owner->AddActorLocalOffset(ZTranslation * DeltaTime, true, &ZHit);

	if (ZHit.bBlockingHit && !Cast<ABaseEnemy>(ZHit.GetActor()))
	{
		const float ResultAngle = UKismetMathLibrary::DegAcos(FVector::DotProduct(ZHit.Normal, FVector::UpVector));
		if (ResultAngle < MaxSlopeAngle)
		{
			if (!bDidTouchGround)
			{
				const float MaxSlopeRadAngle = FMath::DegreesToRadians(MaxSlopeAngle);

				// Perform a linetrace to make sure that there's nothing
				// Below us, since there's a discrepancy between collision
				// on stairs and collision by edges. If there's nothing directly
				// below us, we should just start falling, even if we're barely
				// Touching the edge at the same time.
				FVector Start = GetActorLocation() * FVector::DownVector * Capsule->GetScaledCapsuleHalfHeight_WithoutHemisphere();

				// Line trace should end at the furthest reachable point with
				// the character's slope limit.
				FVector EndOffset = FVector::DownVector * (Capsule->GetScaledCapsuleRadius() + Capsule->GetScaledCapsuleRadius() * FMath::FastAsin(MaxSlopeRadAngle));
				FVector End = Start + EndOffset;

				ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_WorldDynamic);
				TArray<AActor*> Ignore;
				Ignore.Add(Owner);

				FHitResult LineHit;
				EDrawDebugTrace::Type DebugTrace = EDrawDebugTrace::None;

				bDidTouchGround = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, TraceType, true, Ignore, DebugTrace, LineHit, true);
			}
		}

		if (ResultAngle >= MaxSlopeAngle || !bDidTouchGround)
		{
			// Recursive check to push us out of any possible collision.
			int IterationLimit = 5;
			while (IterationLimit > 0 && !ZTranslation.IsNearlyZero())
			{
				// If we somehow end up intersecting with a surface,
				// push us out before continuing on, because otherwise
				// we might be stuck.
				if (ZHit.bStartPenetrating)
				{
					int PeneIterationLimit = 5;
					FHitResult PeneHit = ZHit;
					while (PeneIterationLimit > 0 && PeneHit.bStartPenetrating)
					{
						// Push us out along the normal, according to how deep
						// into the sdurface we are.
						FVector Pushout = PeneHit.Normal * (PeneHit.PenetrationDepth + 1.0001f);
						Owner->AddActorLocalOffset(Pushout, true, &PeneHit);

						PeneIterationLimit--;
					}
				}

				FVector HitNormal = ZHit.Normal;
				// Project along the wall slope.
				ZTranslation = FVector::VectorPlaneProject(ZTranslation, HitNormal);

				Owner->AddActorLocalOffset(ZTranslation * DeltaTime, true, &ZHit);

				// Exit prematurely if we didn't collide with anything this sweep
				if (!ZHit.bBlockingHit)
					break;

				IterationLimit--;
			}
		}
	}
#pragma endregion

#pragma region Horizontal
	
	Owner->AddActorWorldOffset(Translation * DeltaTime, true, &Hit);
	
	if (Hit.bBlockingHit && !Cast<ABaseEnemy>(Hit.GetActor()))
	{
		// Same iterative process as in vertical.
		int IterationLimit = 5;
		while (IterationLimit > 0 && !Translation.IsNearlyZero())
		{
			// (If we somehow end up intersecting with a surface,
			// push us out before continuing on, because otherwise
			// we might be rendered stuck.)
			if (Hit.bStartPenetrating)
			{
				int PeneIterationLimit = 5;
				FHitResult PeneHit = Hit;
				while (PeneIterationLimit > 0 && PeneHit.bStartPenetrating)
				{
					FVector Pushout = PeneHit.Normal * (PeneHit.PenetrationDepth + 1.0001f);
					Owner->AddActorWorldOffset(Pushout, PeneIterationLimit > 1, &PeneHit);

					PeneIterationLimit--;
				}
			}

			FVector HitNormal = Hit.Normal;

			const float ResultAngle = UKismetMathLibrary::DegAcos(FVector::DotProduct(HitNormal, FVector::UpVector));
			bApplyToTestSpeed = ResultAngle >= MaxSlopeAngle;

			const float SlantedWallClamp = 80.f;
			if (ResultAngle > SlantedWallClamp)
			{
				HitNormal.Z = 0;
				HitNormal.Normalize();
			}

			Translation = FVector::VectorPlaneProject(Translation, HitNormal);//SpeedApplyTranslation

			// Project along the ground.
			Owner->AddActorWorldOffset(Translation * DeltaTime, true, &Hit);
			// Exit prematurely if we didn't collide with anything this sweep.
			if (!Hit.bBlockingHit)
				break;

			IterationLimit--;
		}

		if (IterationLimit == 0)
			Translation = FVector::ZeroVector;
	}
#pragma endregion

	if (bApplyToTestSpeed)
		TestVelocity = FVector(Translation.X, Translation.Y, TestVelocity.Z);

	bTestOnGround = bDidTouchGround;
}







