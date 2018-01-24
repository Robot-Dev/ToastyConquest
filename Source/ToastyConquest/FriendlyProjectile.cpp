/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "FriendlyProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Animal.h"
#include "Human.h"


void AFriendlyProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
	AHuman* Enemy = Cast<AHuman>(OtherActor);
	AAnimal* Animal = Cast<AAnimal>(OtherActor);
	if (Animal || Enemy) {
		if (ProjectileMovement) {
		ProjectileMovement->StopMovementImmediately();
		ProjectileMovement->ProjectileGravityScale = 0.0f;
		}
	}
}


