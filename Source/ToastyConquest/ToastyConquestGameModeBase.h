/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToastyConquestGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOASTYCONQUEST_API AToastyConquestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	bool bFightModeOn = false;

public:
	AToastyConquestGameModeBase();

	void SetFightMode(bool bFightMode);

	/** Returns whether the toaster can climb **/
	UFUNCTION(BlueprintCallable, Category = "Fight Mode")
	FORCEINLINE bool IsFightModeOn() const { return bFightModeOn; }
};
