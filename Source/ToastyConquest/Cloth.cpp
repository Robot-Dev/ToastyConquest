/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "Cloth.h"

#include "Toaster.h"
#include "ToasterController.h"

#include "Components/BoxComponent.h"

/** Constructor */

ACloth::ACloth() {
	CollisionComponent->SetBoxExtent(FVector(50.0f, 0.0f, 250.0f));
	PrimaryActorTick.bCanEverTick = true;
}

/** Tick */

void ACloth::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	if (!World) {
		return;
	}

	AToasterController* Controller = Cast<AToasterController>(World->GetFirstPlayerController());
	if (!Controller) {
		return;
	}

	AToaster* Toaster = Cast<AToaster>(Controller->GetPawn());
	if (!Toaster) {
		return;
	}
	
	if (IsOverlappingActor(Toaster)) {

		if (GetActorLocation().X > Toaster->GetActorLocation().X) {
			Toaster->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
		else {
			Toaster->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
	}
}