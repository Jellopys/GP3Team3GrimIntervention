// Author Richard Hill - FutureGames

#pragma once

#include "CoreMinimal.h"
#include "CustomComponents/Combat/AuraComponent.h"
#include "CustomComponents/Movement/MovementData.h"
#include "PlayerCharacter.generated.h"

class AForwardProjectile;
class AScytheProjectile;
class UGrimGameInstance;
class UCapsuleComponent;
class UCameraComponent;
class UInputComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class APawn;
class UStaticMeshComponent;

class UCombatComponent;
class UHealthComponent;
class UPlayerMovementComponent;
class AGrimPlayerController;
class ABaseSpell;
class AGrimGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScytheCast);
UCLASS()
class APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	// Spells
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spells)
	TSubclassOf<ABaseSpell> Spell;
	UPROPERTY()
	ABaseSpell* CurrentSpell;
	UFUNCTION()
	void PerformAttack();
	void ReleasePrimary();
	UFUNCTION()
	void RotateTowardMouse(const bool Enabled);
	UFUNCTION()
	float PlayAnimationMontage(UAnimMontage* Montage, float InPlayRate, FName StartSectionName);
	UFUNCTION(BlueprintCallable)
	void SetIsAttacking(bool InBool);
	UFUNCTION(BlueprintImplementableEvent)
	void OnReturnScythe();
	UFUNCTION(BlueprintImplementableEvent)
	void OnScytheCast();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ScytheMesh;
	UFUNCTION(BlueprintCallable)
	void SetIsCasting(bool IsCasting);
	UPROPERTY(BlueprintReadWrite)
	AScytheProjectile* ScytheSpawned;

	/////// Animations
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* KickMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* DashMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* ScytheTossMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ScytheTossAnimFreeMove = 0.6f;

	/////// Components
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	UCapsuleComponent* Capsule;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	UHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UPlayerMovementComponent* MovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* FirePos;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> MouseOrb;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
	UAuraComponent* AuraComponent;

	////// Variables
	//// MOVEMENT
	UPROPERTY(BlueprintReadWrite, Category = Movement)
	bool bIsAllowedToMove = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsCasting = false;
	UPROPERTY(EditAnywhere, Category = Movement)
	float TurnRate = 0.3f;
	FVector PrevVelocity = FVector::ZeroVector;
	float TurnDelta = 0;
	UPROPERTY(EditAnywhere, Category = Movement)
	float TurnSpeed = 10;

	// Stamina
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MaxStamina = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float CurrentStamina = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float StaminaGainMultiplier = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	bool CanRechargeStamina = true;
	FTimerHandle StaminaTimerDelegate;

	// Dash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float DashPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float DashDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float DashCooldown = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float DashStaminaCost = 20;
	UPROPERTY(BlueprintReadWrite, Category = Movement)
	bool bDashLegal = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	bool Dashing = false;
	UPROPERTY()
	float CachedDashDuration;
	
	//// Camera
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Camera)
	float CameraRotationSpeed = 20;
	UPROPERTY()
	bool bRotatingCamera;

	//// MouseOrb
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MouseOrb)
	float MouseOrbLerpSpeed = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MouseOrb)
	AActor* MouseOrbVisual;
	UPROPERTY()
	FVector2D MousePosition;
	UPROPERTY()
	bool bIsOrbActive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KickTimer = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AScytheProjectile> ScytheProjectile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AForwardProjectile> TestProjectile;
	
	//// Getters
	UCapsuleComponent* GetCapsule() const { return Capsule; }
	UCameraComponent* GetCamera();
	AActor* GetOrb();
	UFUNCTION(BlueprintCallable)
	FVector GetPlayerFuturePos(float InDeltaFrames);
	UHealthComponent* GetHealthComponent();

	//// Events
	UFUNCTION(BlueprintCallable)
	void UseStamina(float StaminaCost, bool ActivateRegainCooldown);
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerDeath();
	UFUNCTION(BlueprintCallable)
	void ForceCancelAnimation();
	UFUNCTION(BlueprintCallable)
	void SetCanMove(bool CanMove);
	UFUNCTION(BlueprintCallable)
	void SpawnScytheProjectile();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	AGrimPlayerController* PlayerController;
	UPROPERTY()
	AGrimGameMode* GrimGameMode;
	UPROPERTY()
	UGrimGameInstance* GrimGameInstance;
	UPROPERTY()
	UMovementData* MovementData;

	float CameraPitch;
	float CameraRoll;
	
	UPROPERTY(BlueprintReadOnly)
	FVector Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Deceleration = 1;
	float Speed;
	float Gravity;
	FVector InputVector = FVector::ZeroVector;
	FVector LookVector = FVector::ZeroVector;
	FRotator CurrentRot;
	bool bIsAttacking = false;
	bool bIsKicking = false;
	FRotator CameraTargetRotation = FRotator::ZeroRotator;
	bool PrevEnabled = false;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnDash(FVector Pos, FRotator Rot);
	UFUNCTION(BlueprintImplementableEvent)
	void OnDashEnd();
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttack();
	UFUNCTION(BlueprintImplementableEvent)
	void OnReleasePrimary();
	UFUNCTION(BlueprintImplementableEvent)
	void OnKick();
	
	void CastScythe();
	void ScytheReturn();
	void RotateCameraRight();
	void RotateCameraLeft();
	void Kick();
	void KickEnd();
	void RegainStaminaRecharge();
	bool CheckStaminaCost(float StaminaCost);
	void HandleStamina(float DeltaTime);
	void RotateCamera(float DeltaTime);
	void EnableCameraRotation();
	void ReleaseCamera();
	void HandleInput(float DeltaTime);
	void MovePlayer(float DeltaTime);
	void MoveForward(float Val);
	void MoveRight(float Val);
	void Dash();
	void OnDashC();
	void OnDashEndC();
	void CheckDash();
	void UpdateMousePosition(float DeltaTime);
	void RotatePlayer(float DeltaTime);
};

