/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "EnemyProjectile.h"
#include "Eye.generated.h"

class UAudioComponent;

/**
 * 
 */
UCLASS()
class TOASTYCONQUEST_API AEye : public AEnemyProjectile
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* EyeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	float ProjectileSpeed = 500.0f;

	FTimerHandle EyeReturnHandle;

	/** Begin Play and Tick*/
	virtual void BeginPlay() override;

	void ReverseMovement();

public:
	AEye();
	
	
};
