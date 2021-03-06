/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "Teeth.h"

#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "Sound/SoundCue.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"

#include "Toaster.h"
#include "ToasterController.h"

#include "Kismet/GameplayStatics.h"

/** Constructor */

ATeeth::ATeeth() {
	PrimaryActorTick.bCanEverTick = true;

	/** Setup Collision Component */
	CollisionComponent->InitSphereRadius(50.0f);

	/** Setup Sprite Component */
	Sprite->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	/** Setup Audio Component */
	TeethSound = CreateDefaultSubobject<UAudioComponent>("TeethSound");

	/** Other */
	Damage = 1.0f;
	InitialLifeSpan = 20.0f;
}


/** Begin Play */

void ATeeth::BeginPlay() {
	Super::BeginPlay();
}

void ATeeth::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AToasterController* ToasterController = Cast<AToasterController>(GetWorld()->GetFirstPlayerController());
	if (ToasterController) {
		AToaster* Toaster = Cast<AToaster>(ToasterController->GetPawn());
		if (Toaster) {
			FVector ToasterLocation = Toaster->GetActorLocation();
			FVector TeethLocation = GetActorLocation();
			FVector DirectionVector = ToasterLocation - TeethLocation;
			DirectionVector.Normalize();

			ProjectileMovement->Velocity = ProjectileVelocity * DirectionVector;
		}
	}
}