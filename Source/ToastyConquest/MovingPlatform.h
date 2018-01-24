/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "TCObject.h"
#include "MovingPlatform.generated.h"

/**
*
*/
UCLASS()
class TOASTYCONQUEST_API AMovingPlatform : public ATCObject
{
	GENERATED_BODY()
	
protected:
	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UInterpToMovementComponent* PlatformMovement;

public:
	AMovingPlatform();
	
};
