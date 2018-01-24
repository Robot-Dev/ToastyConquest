/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "GameFramework/Actor.h"
#include "TCObject.generated.h"

UCLASS()
class TOASTYCONQUEST_API ATCObject : public AActor
{
	GENERATED_BODY()
	
protected:
	/** Capsule collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionComponent;

	/** Sprite component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* Sprite;

public:
	ATCObject();
};
