/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "TCObject.h"
#include "Cloth.generated.h"

UCLASS()
class TOASTYCONQUEST_API ACloth : public ATCObject
{
	GENERATED_BODY()

protected:
	virtual void Tick(float DeltaTime) override;

public:
	ACloth();
};
