/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/


#pragma once

#include "Projectile.h"
#include "FriendlyProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TOASTYCONQUEST_API AFriendlyProjectile : public AProjectile
{
	GENERATED_BODY()
	
protected:
/** Overlap and Hit Methods */
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;
	
};
