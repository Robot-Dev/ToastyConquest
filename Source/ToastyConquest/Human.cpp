/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "Human.h"

#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "Sound/SoundCue.h"

#include "ToastyConquestGameModeBase.h"
#include "Toaster.h"

#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


/** Constructor */

AHuman::AHuman() {
	/** Setup Sound Component */
	KnockBackSound = CreateDefaultSubobject<USoundCue>(TEXT("KnockBackSound"));
	DamagedSound = CreateDefaultSubobject<USoundCue>(TEXT("DamagedSound"));
	DeathSound = CreateDefaultSubobject<USoundCue>(TEXT("DeathSound"));
}

/** Begin Play and Tick */

void AHuman::BeginPlay() {
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AHuman::OnHit);

	GetWorldTimerManager().SetTimer(Attack1Handle, this, &AHuman::Attack1, Attack1FirstCooldown, false);
	GetWorldTimerManager().SetTimer(Attack2Handle, this, &AHuman::Attack2, Attack2FirstCooldown, false);

	UWorld* World = GetWorld();
	if (!World) {
		return;
	}

	AToastyConquestGameModeBase* GameMode = Cast<AToastyConquestGameModeBase>(World->GetAuthGameMode());
	if (GameMode) {
		GameMode->SetFightMode(true);
	}
}

void AHuman::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	UpdateRotation();
}

void AHuman::UpdateRotation() {
	UWorld* World = GetWorld();
	if (!World) {
		return;
	}

	APlayerController* Controller = World->GetFirstPlayerController();
	if (!Controller) {
		return;
	}

	APawn* Pawn = Controller->GetPawn();
	if (!Pawn) {
		return;
	}

	if (Pawn->GetActorLocation().X - GetActorLocation().X >= 0.0f) {
		SetActorRotation(FRotator(0.0, 0.0f, 0.0f));
	}
	else {
		SetActorRotation(FRotator(0.0, 180.0f, 0.0f));
	}
}

/** Overlap and Hit Methods */

void AHuman::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	AToaster* Toaster = Cast<AToaster>(OtherActor);
	if (Toaster) {
		KnockBack(Toaster);
	}
}

/** Other Methods */

void AHuman::KnockBack(AToaster* Toaster) {
	float RelativePositionX = Toaster->GetActorLocation().X - GetActorLocation().X > 0.0f ? 1.0f : -1.0f;
	Toaster->LaunchCharacter(KnockBackDistance * (FVector(RelativePositionX, 0, 0)), true, true);
	Toaster->TakeDamage(1.0f);

	if (KnockBackSound) {
		UGameplayStatics::PlaySoundAtLocation(this, KnockBackSound, GetActorLocation());
	}
}

void AHuman::TakeDamage(float Damage) {
	if (bIsInvincible) {
		return;
	}

	Health -= Damage;

	OnHurt();

	if (Health > 0) {
		if (DamagedSound) {
			UGameplayStatics::PlaySoundAtLocation(this, DamagedSound, GetActorLocation());
		}
	}
	else {
		Die();
	}
}

void AHuman::Die() {
	UWorld* World = GetWorld();
	if (!World) {
		return;
	}

	AToastyConquestGameModeBase* GameMode = Cast<AToastyConquestGameModeBase>(World->GetAuthGameMode());
	if (GameMode) {
		GameMode->SetFightMode(false);
	}

	Destroy();
}

void AHuman::Attack1() {
	GetWorldTimerManager().SetTimer(Attack1Handle, this, &AHuman::Attack1, Attack1Cooldown, false);
}

void AHuman::Attack2() {
	GetWorldTimerManager().SetTimer(Attack2Handle, this, &AHuman::Attack2, Attack2Cooldown, false);
}