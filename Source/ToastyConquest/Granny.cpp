/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "Granny.h"

#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#include "Teeth.h"
#include "Eye.h"

#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AGranny::AGranny() {
	/** Setup Capsule Component */
	UCapsuleComponent* CapsuleComponent = GetCapsuleComponent();
	CapsuleComponent->SetCapsuleHalfHeight(550.0f);
	CapsuleComponent->SetCapsuleRadius(300.0f);

	/** Setup Sprite Component */
	UPaperFlipbookComponent* Sprite = GetSprite();

	/** Setup Sound Component */
	IdleSound = CreateDefaultSubobject<UAudioComponent>(TEXT("IdleSound"));

	FireTeethSound = CreateDefaultSubobject<USoundCue>(TEXT("FireTeethSound"));
	FireEyeSound = CreateDefaultSubobject<USoundCue>(TEXT("FireEyeSound"));

	/** Setup Teeth */
	Teeth = ATeeth::StaticClass();
	Eye = AEye::StaticClass();

	Health = 15.0f;
}

void AGranny::BeginPlay() {
	Super::BeginPlay();

	IdleSound->Play();
}

void AGranny::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	UpdateState();
	UpdateAnimation();
}

void AGranny::UpdateState() {
	if (bIsDead) {
		GrannyState = EGrannyState::Dead;
		return;
	}

	if (bIsDying) {
		GrannyState = EGrannyState::Dying;
		return;
	}

	if (bIsSpitting) {
		GrannyState = EGrannyState::Spitting;
		return;
	}

	if (bIsThrowingEye) {
		GrannyState = EGrannyState::ThrowingEye;
		return;
	}

	GrannyState = EGrannyState::Idle;
}

void AGranny::UpdateAnimation() {
	switch (GrannyState) {
	case EGrannyState::Idle:
		ChangeAnimation(IdleAnimation);
		break;
	case EGrannyState::Spitting:
		ChangeAnimation(SpitAnimation);
		break;
	case EGrannyState::ThrowingEye:
		ChangeAnimation(ThrowEyeAnimation);
		break;
	case EGrannyState::Dying:
		ChangeAnimation(DeathAnimation);
		break;
	default:
		break;
	}
}

void AGranny::ChangeAnimation(UPaperFlipbook* Animation) {
	UPaperFlipbookComponent* Sprite = GetSprite();
	if (Sprite && Animation && Sprite->GetFlipbook() != Animation) {
		Sprite->SetFlipbook(Animation);
	}
}


void AGranny::Attack1() {
	Super::Attack1();

	bIsSpitting = true;
	FTimerHandle SpittingHandle;
	GetWorldTimerManager().SetTimer(SpittingHandle, this, &AGranny::FireTeeth, 0.5f, false);
}

void AGranny::Attack2() {
	Super::Attack2();

	bIsThrowingEye = true;
	FTimerHandle EyeThrowingHandle;
	GetWorldTimerManager().SetTimer(EyeThrowingHandle, this, &AGranny::FireEye, 0.5f, false);
}

void AGranny::FireTeeth() {
	bIsSpitting = false;

	// Fire projectile
	if (Teeth) {
		UWorld* World = GetWorld();
		if (World) {
			FRotator SpawnRotation = GetActorRotation();
			FVector SpawnLocation = GetActorLocation() + TeethSpawnLocation;
			World->SpawnActor<AProjectile>(Teeth, SpawnLocation, SpawnRotation);
		}
	}

	// Play Fire Sound
	if (FireTeethSound) {
		UGameplayStatics::PlaySoundAtLocation(this, FireTeethSound, GetActorLocation());
	}
}

void AGranny::FireEye() {
	bIsThrowingEye = false;

	// Fire projectile
	if (Eye) {
		UWorld* World = GetWorld();
		if (World) {
			FRotator SpawnRotation = GetActorRotation();
			FVector SpawnLocation = GetActorLocation() + EyeSpawnLocation;
			World->SpawnActor<AProjectile>(Eye, SpawnLocation, SpawnRotation);
		}
	}

	// Play Fire Sound
	if (FireEyeSound) {
		UGameplayStatics::PlaySoundAtLocation(this, FireEyeSound, GetActorLocation());
	}
}

void AGranny::Die() {
	bIsInvincible = true;
	bIsDying = true;

	if (DeathSound) {
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	FTimerHandle DeathHandle;
	GetWorldTimerManager().SetTimer(DeathHandle, [this]() { Super::Die(); }, 0.6f, false);
}