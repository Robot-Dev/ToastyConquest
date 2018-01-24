/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "GameFramework/PlayerController.h"
#include "ToasterController.generated.h"

/**
 * 
 */
UCLASS()
class TOASTYCONQUEST_API AToasterController : public APlayerController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void MoveRight(float Value);

	void Climb(float Value);

	void Jump();

	void StartFire();

	void Fire();

	void Hack();
};
