/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "Projectile.h"
#include "EnemyProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TOASTYCONQUEST_API AEnemyProjectile : public AProjectile
{
	GENERATED_BODY()
	
protected:
	/** Other methods */
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;
};
