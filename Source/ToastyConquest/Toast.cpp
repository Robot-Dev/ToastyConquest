/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "Toast.h"

#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Sound/SoundCue.h"

#include "PaperFlipbook.h"

#include "Toaster.h"
#include "Human.h"
#include "Animal.h"

#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AToast::AToast() {
	CollisionComponent->InitSphereRadius(55.0f);

	ToastExplosionSound = CreateDefaultSubobject<USoundCue>("ToastExplosion");

	ProjectileMovement->Velocity = FVector(200.0f, 0.0f, 200.0f);

	Damage = 1.0f;
	InitialLifeSpan = 2.0f;
}

void AToast::BeginPlay() {
	Super::BeginPlay();
}

void AToast::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AHuman* Enemy = Cast<AHuman>(OtherActor);
	AAnimal* Animal = Cast<AAnimal>(OtherActor);
	if (Animal || Enemy) {
		Explode();
	}
}

void AToast::Explode() {
	if (ToastExplosionAnimation && Sprite->GetFlipbook() != ToastExplosionAnimation) {
		Sprite->SetRelativeRotation(FRotator(0.0f, -25.0f, 0.0f));
		Sprite->SetFlipbook(ToastExplosionAnimation);
	}

	if (ToastExplosionSound) {
		UGameplayStatics::PlaySoundAtLocation(this, ToastExplosionSound, GetActorLocation());
	}

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors) {
		AHuman* Enemy = Cast<AHuman>(OverlappingActor);
		if (Enemy) {
			Enemy->TakeDamage(Damage);
			OnExplode();
			continue;
		}

		AAnimal* Animal = Cast<AAnimal>(OverlappingActor);
		if (Animal) {
			Animal->TakeDamage(Damage);
			OnExplode();
		}
	}


	FTimerHandle DestroyHandle;
	GetWorldTimerManager().SetTimer(DestroyHandle, [this]() { Destroy(); }, 0.5f, false);
}