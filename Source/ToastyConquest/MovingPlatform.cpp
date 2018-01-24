/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "MovingPlatform.h"

#include "Components/BoxComponent.h"
#include "Components/InterpToMovementComponent.h"

AMovingPlatform::AMovingPlatform() {
	/** Setup Projectile Movement Component */
	PlatformMovement = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("PlatformMovementComponent"));
	PlatformMovement->UpdatedComponent = CollisionComponent;
}
