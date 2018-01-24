/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "Eye.h"

#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"

#include "Toaster.h"
#include "ToasterController.h"

#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AEye::AEye() {
	/** Setup Collision Component */
	CollisionComponent->InitSphereRadius(48.0f);

	/** Setup Audio Component */
	EyeSound = CreateDefaultSubobject<UAudioComponent>("EyeSound");

	/** Other */
	Damage = 1.0f;
	InitialLifeSpan = 4.0f;
}


/** Begin Play */

void AEye::BeginPlay() {
	Super::BeginPlay();

	AToasterController* ToasterController = Cast<AToasterController>(GetWorld()->GetFirstPlayerController());
	if (ToasterController) {
		AToaster* Toaster = Cast<AToaster>(ToasterController->GetPawn());
		if (Toaster) {
			FVector ToasterLocation = Toaster->GetActorLocation();
			FVector TeethLocation = GetActorLocation();
			FVector DirectionVector = ToasterLocation - TeethLocation;
			DirectionVector.Normalize();

			ProjectileMovement->Velocity = ProjectileSpeed * DirectionVector;
		}
	}

	GetWorldTimerManager().SetTimer(EyeReturnHandle, this, &AEye::ReverseMovement, InitialLifeSpan / 2, false);
}


void AEye::ReverseMovement() {
	ProjectileMovement->Velocity = -(ProjectileMovement->Velocity);
}


