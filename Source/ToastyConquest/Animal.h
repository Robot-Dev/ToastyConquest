/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "TCAnimatedObject.h"
#include "Animal.generated.h"

UCLASS()
class TOASTYCONQUEST_API AAnimal : public ATCAnimatedObject
{
	GENERATED_BODY()
	
protected:
/** Health */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float Health = 1.0f;

public:	
	AAnimal();

	void TakeDamage(float Damage);
};
