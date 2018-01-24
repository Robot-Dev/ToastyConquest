/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "EnemyProjectile.h"

#include "Toaster.h"

void AEnemyProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
	AToaster* Toaster = Cast<AToaster>(OtherActor);
	if (Toaster) {
		Toaster->TakeDamage(Damage);
		Destroy();
	}
}


