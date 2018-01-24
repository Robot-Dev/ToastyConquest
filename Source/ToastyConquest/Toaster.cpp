/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "Toaster.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#include "ToasterController.h"
#include "Toast.h"
#include "Appliance.h"
#include "Cloth.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

/** Constructor */

AToaster::AToaster()
{
	/** Setup Capsule Component */
	UCapsuleComponent* CapsuleComponent = GetCapsuleComponent();
	CapsuleComponent->SetCapsuleHalfHeight(100.0f);
	CapsuleComponent->SetCapsuleRadius(60.0f);
	CapsuleComponent->bGenerateOverlapEvents = true;

	/** Setup Spring Arm Component */
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 960.0f;
	SpringArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);
	SpringArmComponent->bAbsoluteRotation = true;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);

	/** Setup Camera Component */
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCameraComponent"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Perspective;
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	SideViewCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	/** Setup Character Movement Component */
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->JumpZVelocity = 900.0f;
	MovementComponent->GravityScale = 2.0f;
	MovementComponent->AirControl = 0.5f;
	MovementComponent->GroundFriction = 3.0f;
	MovementComponent->MaxStepHeight = 0.0f;
	MovementComponent->MaxWalkSpeed = 800.0f;
	MovementComponent->MaxFlySpeed = 800.0f;
	MovementComponent->BrakingDecelerationFlying = 10000.0f;
	MovementComponent->bUseFlatBaseForFloorChecks = true;

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	MovementComponent->bOrientRotationToMovement = false;
	MovementComponent->bConstrainToPlane = true;
	MovementComponent->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	/** Setup Sprite Component */
	GetSprite()->SetFlipbook(CreateDefaultSubobject<UPaperFlipbook>(TEXT("Sprite")));
	GetSprite()->SetRelativeLocation(FVector(10.0f, 0.0f, 26.0f));
	GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	GetSprite()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	/** Setup Projectile Component */
	Toast = AToaster::StaticClass();

	/** Setup Sound Component */
	IdleSound = CreateDefaultSubobject<UAudioComponent>(TEXT("IdleSound"));
	RunningSound = CreateDefaultSubobject<UAudioComponent>(TEXT("RunningSound"));
	FallingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("FallingSound"));
	ClimbingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ClimbingSound"));
	JumpingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("JumpingSound"));
	HackingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("HackingSound"));
	HurtingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("HurtingSound"));
	DyingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DyingSound"));

	LandSound = CreateDefaultSubobject<USoundCue>(TEXT("LandSound"));
	FireSound = CreateDefaultSubobject<USoundCue>(TEXT("FireSound"));	
	ReloadSound = CreateDefaultSubobject<USoundCue>(TEXT("ReloadSound"));

	/** Other */
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationYaw = true;
}

/** Begin Play */

void AToaster::BeginPlay() {
	Super::BeginPlay();

	UCapsuleComponent* CapsuleComponent = GetCapsuleComponent();
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AToaster::OnOverlapBegin);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &AToaster::OnOverlapEnd);
}

/** Tick */

void AToaster::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	UpdateRotation();
	UpdateState();
	UpdateAnimation();
	UpdateSound();

	UpdateCharging(DeltaSeconds);
}

void AToaster::UpdateRotation() {
	if (!Controller) {
		return;
	}

	const float PlayerHorizontalDirection = GetVelocity().X;
	if (PlayerHorizontalDirection < 0.0f)
	{
		Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
	}
	else if (PlayerHorizontalDirection > 0.0f)
	{
		Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}

void AToaster::UpdateState() {
	if (bIsDying) {
		ToasterState = EToasterState::Dying;
		return;
	}

	if (bIsHurting) {
		ToasterState = EToasterState::Hurting;
		return;
	}

	if (bIsHacking) {
		ToasterState = EToasterState::Hacking;
		return;
	}

	if (bIsFiring) {
		ToasterState = EToasterState::Firing;
		return;
	}

	if (bIsLanding) {
		ToasterState = EToasterState::Landing;
		return;
	}

	if (bIsClimbing) {
		if (FMath::Abs(GetVelocity().Z) > 1.0f) {
			ToasterState = EToasterState::Climbing;
		}
		else {
			ToasterState = EToasterState::Hanging;
		}
		return;
	}

	if (bIsWallJumping) {
		ToasterState = EToasterState::WallJumping;
		return;
	}

	if (bIsJumping) {
		ToasterState = EToasterState::Jumping;
		return;
	}

	if (FMath::Abs(GetVelocity().Z) > 1.0f || GetCharacterMovement()->MovementMode == MOVE_Falling) {
		ToasterState = EToasterState::Falling;
		return;
	}

	if (FMath::Abs(GetVelocity().X) > 1.0f) {
		ToasterState = EToasterState::Running;
	}
	else {
		ToasterState = EToasterState::Idle;
	}
}

void AToaster::UpdateAnimation() {
	switch (ToasterState) {
	case EToasterState::Idle:
		ChangeAnimation(IdleAnimation);
		break;
	case EToasterState::Running:
		ChangeAnimation(RunAnimation);
		break;
	case EToasterState::Jumping:
		ChangeAnimation(JumpAnimation);
		break;
	case EToasterState::WallJumping:
		ChangeAnimation(WallJumpAnimation);
		break;
	case EToasterState::Falling:
		ChangeAnimation(FallAnimation);
		break;
	case EToasterState::Landing:
		ChangeAnimation(LandAnimation);
		break;
	case EToasterState::Firing:
		ChangeAnimation(FireAnimation);
		break;
	case EToasterState::Hacking:
		ChangeAnimation(HackAnimation);
		break;
	case EToasterState::Climbing:
		ChangeAnimation(ClimbAnimation);
		break;
	case EToasterState::Hanging:
		ChangeAnimation(HangAnimation);
		break;
	case EToasterState::Hurting:
		ChangeAnimation(HurtAnimation);
		break;
	case EToasterState::Dying:
		ChangeAnimation(DeathAnimation);
		break;
	default:
		break;
	}
}

void AToaster::UpdateSound() {
	switch (ToasterState) {
	case EToasterState::Idle:
		ChangeSound(IdleSound);
		break;
	case EToasterState::Running:
		ChangeSound(RunningSound);
		break; 
	case EToasterState::Jumping:
		ChangeSound(JumpingSound);
		break;
	case EToasterState::Falling:
		ChangeSound(FallingSound);
		break;
	case EToasterState::Climbing:
		ChangeSound(ClimbingSound);
		break;
	case EToasterState::Hanging:
		ChangeSound(IdleSound);
		break;
	case EToasterState::Hacking:
		ChangeSound(HackingSound);
		break;
	case EToasterState::Hurting:
		ChangeSound(HurtingSound);
		break;
	case EToasterState::Dying:
		ChangeSound(DyingSound);
		break;
	default:
		break;
	}
}

void AToaster::ChangeAnimation(UPaperFlipbook* Animation) {
	UPaperFlipbookComponent* Sprite = GetSprite();
	if (Sprite && Animation && Sprite->GetFlipbook() != Animation) {
		Sprite->SetFlipbook(Animation);
	}
}

void AToaster::ChangeSound(UAudioComponent* Sound) {
	if (!Sound) {
		return;
	}

	if(!Sound->IsPlaying()) {
		Sound->Play();
	}

	if (Sound != RunningSound) {
		RunningSound->Stop();
	}

	if (Sound != JumpingSound) {
		JumpingSound->Stop();
	}

	if (Sound != FallingSound) {
		FallingSound->Stop();
	}

	if (Sound != ClimbingSound) {
		ClimbingSound->Stop();
	}

	if (Sound != HackingSound) {
		HackingSound->Stop();
	}

	if (Sound != HurtingSound) {
		HurtingSound->Stop();
	}

	if (Sound != DyingSound) {
		DyingSound->Stop();
	}
}

void AToaster::UpdateCharging(float DeltaSeconds) {
	// Update ChargeTime
	if (bIsCharging) {
		ProjectileChargeTime += DeltaSeconds;
		if (ProjectileChargeTime > ProjectileMaxChargeTime) {
			ProjectileChargeTime = ProjectileMaxChargeTime;
		}
	}

	// Set sprite color based on charged time
	float SpriteColorCoef = ProjectileMaxChargeTime - 0.66 * ProjectileChargeTime;
	GetSprite()->SetSpriteColor(FLinearColor(1.0f, SpriteColorCoef, SpriteColorCoef, 1.0f));
}

/** Movement */

void AToaster::MoveRight(float Value) {
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void AToaster::Climb(float Value) {
	AddMovementInput(FVector(0.0f, 0.0f, 1.0f), Value);
}

void AToaster::Jump() {
	if (IsTouchingWall() && (bIsJumping || ToasterState == EToasterState::Falling)) {
		WallJump();
	}
	else if(CanJump()) {
		bIsJumping = true;

		FTimerHandle JumpStateHandle;
		GetWorldTimerManager().SetTimer(JumpStateHandle, [this]() { bIsJumping = false; }, 0.66f, false);

		Super::Jump();
	}
}

void AToaster::WallJump() {
	float JumpVelocity = GetCharacterMovement()->JumpZVelocity;
	FVector LaunchDirection = FVector(-JumpVelocity * GetActorForwardVector().X, 0, JumpVelocity);

	bIsWallJumping = true;

	FTimerHandle WallJumpStateHandle;
	GetWorldTimerManager().SetTimer(WallJumpStateHandle, [this]() { bIsWallJumping = false; }, 0.2f, false);

	LaunchCharacter(LaunchDirection, true, true);

	if (LandSound) {
		UGameplayStatics::PlaySoundAtLocation(this, LandSound, GetActorLocation());
	}
}

bool AToaster::IsTouchingWall() {
	FVector ActorLocation = GetActorLocation() + (1.0f * GetCapsuleComponent()->GetScaledCapsuleRadius()) * GetActorForwardVector();
	FVector LineTraceEnd = GetActorLocation() + (2.0f * GetCapsuleComponent()->GetScaledCapsuleRadius()) * GetActorForwardVector();

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(
		HitResult, ActorLocation, LineTraceEnd, ECollisionChannel::ECC_Visibility
	);

	return HitResult.bBlockingHit;
}

void AToaster::Landed(const FHitResult& Hit) {
	Super::OnLanded(Hit);

	bIsLanding = true;

	FTimerHandle LandStateHandle;
	GetWorldTimerManager().SetTimer(LandStateHandle, [this]() { bIsLanding = false; }, 0.3f, false);

	if (LandSound) {
		UGameplayStatics::PlaySoundAtLocation(this, LandSound, GetActorLocation());
	}
}

/** Fire */

void AToaster::StartFire() {
	if (ProjectileCount <= 0) {
		return;
	}

	bIsCharging = true;
}

void AToaster::Fire() {
	if (!bIsCharging || ProjectileCount <= 0) {
		return;
	}

	// Decrement projectile count and set cooldown
	ProjectileCount--;

	FTimerHandle ReloadCooldownHandle;
	GetWorldTimerManager().SetTimer(ReloadCooldownHandle, this, &AToaster::Reload, ReloadCooldown, false);

	// Update firing state
	bIsCharging = false;
	bIsFiring = true;

	FTimerHandle FireStateHandle;
	GetWorldTimerManager().SetTimer(FireStateHandle, [this]() { bIsFiring = false; }, 0.3f, false);

	// Fire projectile
	if (Toast) {
		UWorld* World = GetWorld();
		if (World) {
			const FVector SpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

			FRotator SpawnRotation;
			if (GetActorRotation().Yaw == 0.0f) {
				SpawnRotation = FRotator(0.0f, -45.0f, 0.0f);
			}
			else {
				SpawnRotation = FRotator(0.0f, 225.0f, 0.0f);
			}

			AProjectile* Projectile = World->SpawnActor<AProjectile>(Toast, SpawnLocation, SpawnRotation);
			
			if (Projectile) {
				UProjectileMovementComponent* ProjectileMovement = Projectile->GetProjectileMovement();
				if (ProjectileMovement) {
					ProjectileMovement->Velocity = GetVelocity() + (1 + ProjectileChargeTime) * ProjectileMovement->Velocity;
				}
			}
		}
	}

	ProjectileChargeTime = 0.0f;

	// Play shooting sound
	if (FireSound)	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

void AToaster::Reload() {
	++ProjectileCount;

	if (ReloadSound) {
		UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
	}
}

/** Hack */

void AToaster::Hack() {
	bIsHacking = true;

	FTimerHandle HackStateHandle;
	GetWorldTimerManager().SetTimer(HackStateHandle, [this]() { bIsHacking = false; }, 1.0f, false);

	TSet<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (auto OverlappingActor : OverlappingActors) {
		AAppliance* Appliance = Cast<AAppliance>(OverlappingActor);
		if (Appliance) {
			Appliance->Hack();
			return;
		}
	}
}

/** Take Damage and Die */

void AToaster::TakeDamage(float Damage) {
	if (bIsInvincible) {
		return;
	}

	Health -= Damage;
	if (Health > 0) {
		bIsInvincible = true;
		bIsHurting = true;

		FTimerHandle HurtHandle;
		GetWorldTimerManager().SetTimer(HurtHandle, [this]() { bIsInvincible = bIsHurting = false; }, 1.0f, false);

		OnHurt();
	}
	else {
		Die();
	}
}

void AToaster::Die() {
	// Update death state
	bIsDying = true;
	bIsInvincible = true;

	// Disable input
	UnPossessed();

	FTimerHandle DeathHandle;
	GetWorldTimerManager().SetTimer(DeathHandle, this, &AToaster::OnDeath, 2.0f);
}

/** Overlap and Hit Methods */

void AToaster::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	ACloth* Cloth = Cast<ACloth>(OtherActor);
	if (Cloth) {
		bCanClimb = true; // TODO: Maybe redundant
		bIsClimbing = true;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	}
}

void AToaster::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	ACloth* Cloth = Cast<ACloth>(OtherActor);
	if (Cloth) {
		bCanClimb = false; // TODO: Maybe redundant
		bIsClimbing = false;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

