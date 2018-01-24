 /*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "TCAnimatedObject.h"
#include "Appliance.generated.h"

UCLASS()
class TOASTYCONQUEST_API AAppliance : public ATCAnimatedObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Active, meta = (AllowPrivateAccess = "true"))
	bool bActive = true;

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnHacked();

public:
	AAppliance();

	void Hack();
};
