/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "GameFramework/Actor.h"
#include "TCAnimatedObject.generated.h"

class UBoxComponent;
class UPaperFlipbookComponent;

UCLASS()
class TOASTYCONQUEST_API ATCAnimatedObject : public AActor
{
	GENERATED_BODY()
	
protected:
	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionComponent;

	/** Sprite component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* Sprite;

public:
	ATCAnimatedObject();
};
