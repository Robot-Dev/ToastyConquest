/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "PaperCharacter.h"
#include "Toaster.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPaperFlipbook;
class USoundCue;
class UAudioComponent;

class AProjectile;

/**
* State Machine for the Toaster class
*/
UENUM(BlueprintType)
enum class EToasterState : uint8
{
	Idle 		UMETA(DisplayName = "Idle"),
	Running		UMETA(DisplayName = "Running"),
	Jumping		UMETA(DisplayName = "Jumping"),
	WallJumping UMETA(DisplayName = "WallJumping"),
	Falling		UMETA(DisplayName = "Falling"),
	Landing		UMETA(DisplayName = "Landing"),
	Firing		UMETA(DisplayName = "Firing"),
	Hacking		UMETA(DisplayName = "Hacking"),
	Climbing	UMETA(DisplayName = "Climbing"),
	Hanging		UMETA(DisplayName = "Hanging"),
	Hurting		UMETA(DisplayName = "Hurting"),
	Dying		UMETA(DisplayName = "Dying")
};

/**
* This class is the default character for ToastyConquest, and it is responsible for all
* physical interaction between the player and the world.
*
* The capsule component (inherited from ACharacter) handles collision with the world
* The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
* The Sprite component (inherited from APaperCharacter) handles the visuals
*/
UCLASS()
class TOASTYCONQUEST_API AToaster : public APaperCharacter
{
	GENERATED_BODY()

protected:
/** Camera **/
	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;


/** Toaster State */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	EToasterState ToasterState;

/** Animations **/
	/** The animation to play while being idle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* IdleAnimation;

	/** The animation to play while running around */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* RunAnimation;

	/** The animation to play while jumping */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* JumpAnimation;

	/** The animation to play while wall-jumping */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* WallJumpAnimation;

	/** The animation to play while falling */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* FallAnimation;

	/** The animation to play while falling */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* LandAnimation;

	/** The animation to play when toast is fired */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* FireAnimation;

	/** The animation to play when hack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* HackAnimation;

	/** The animation to play while climbing */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* ClimbAnimation;

	/** The animation to play while hanging */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* HangAnimation;

	/** The animation to play when hurting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* HurtAnimation;

	/** The animation to play when killed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* DeathAnimation;

	FTimerHandle FireAnimationTimeHandle;

/** Sounds */
	/** Looping sounds */
	/** The sound to play when idle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* IdleSound;

	/** The sound to play when running */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* RunningSound;

	/** The sound to play when falling */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* FallingSound;

	/** The sound to play when climbing */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* ClimbingSound;

	/** The sound to play when toaster jumps */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* JumpingSound;
	
	/** The sound to play when toaster is hacking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* HackingSound;

	/** The sound to play when damaged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* HurtingSound;

	/** The sound to play when damaged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* DyingSound;

	/** Single sounds */
	/** The sound to play when toaster lands or wall jumps */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	USoundCue* LandSound;

	/** The sound to play when toast is fired */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	USoundCue* FireSound;

	/** The sound to play when new toast is ready */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	USoundCue* ReloadSound;

/** Projectile */
	/** Projectile to be fired */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> Toast;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	int32 ProjectileCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	float ProjectileChargeTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	float ProjectileMaxChargeTime = 1.0f;

	/** Toast Fire Reload Cooldown */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	float ReloadCooldown = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	float FireOffset = 50.0f;
	
	bool bIsCharging = false;
	bool bIsFiring = false;
	bool bIsHacking = false;

/** Health */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float Health = 3.0f;

	bool bIsInvincible = false;
	bool bIsDying = false;
	bool bIsHurting = false;

/** Movement */
	bool bIsJumping = false;
	bool bIsWallJumping = false;
	bool bCanClimb = false;
	bool bIsClimbing = false;
	bool bIsLanding = false;

/** Begin Play and Tick */

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

/** Tick submethods **/

	void UpdateRotation();

	void UpdateState();

	void UpdateAnimation();

	void UpdateSound();

/** Overlap and Hit Methods */
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

/** Other methods */
	void ChangeAnimation(UPaperFlipbook* Animation);

	void ChangeSound(UAudioComponent* Sound);

	bool IsTouchingWall();

	void WallJump();

	void UpdateCharging(float DeltaSeconds);

	void Reload();

	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void Die();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnHurt();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnDeath();


public:
	AToaster();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void TakeDamage(float Damage);

	void MoveRight(float Value);

	virtual void Jump() override;

	void Hack();

	void StartFire();

	void Fire();

	void Climb(float Value);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }

	/** Returns whether the toaster can climb **/
	FORCEINLINE bool CanClimb() const { return bCanClimb; }
};
