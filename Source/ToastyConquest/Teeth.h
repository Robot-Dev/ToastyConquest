/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "EnemyProjectile.h"
#include "Teeth.generated.h"

class UAudioComponent;

/**
 * 
 */
UCLASS()
class TOASTYCONQUEST_API ATeeth : public AEnemyProjectile
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* TeethSound;
	
	/** The real teeth speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float ProjectileVelocity = 100.0f;

/** Begin Play and Tick*/
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	ATeeth();
	
};
