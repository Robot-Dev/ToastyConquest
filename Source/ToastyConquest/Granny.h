/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "Human.h"
#include "Granny.generated.h"

class ATeeth;
class AEye;
class UPaperFlipbook;
class UAudioComponent;

/**
* State Machine for the Granny class
*/
UENUM(BlueprintType)
enum class EGrannyState : uint8
{
	Idle 			UMETA(DisplayName = "Idle"),
	Spitting		UMETA(DisplayName = "Spitting"),
	ThrowingEye		UMETA(DisplayName = "ThrowingEye"),
	Dying			UMETA(DisplayName = "Dying"),
	Dead			UMETA(DisplayName = "Dead")
};

/**
 * 
 */
UCLASS()
class TOASTYCONQUEST_API AGranny : public AHuman
{
	GENERATED_BODY()

private:
/** Projectiles */
	/** Teeth to be fired */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ATeeth> Teeth;

	/** Eye to be fired */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEye> Eye;

/** Sounds*/
/** The sound to play when idle  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* IdleSound;

	/** The sound to play when teeth are fired */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	USoundCue* FireTeethSound;

	/** The sound to play when eye is fired */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	USoundCue* FireEyeSound;

/** Animations **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	EGrannyState GrannyState;

	/** The animation to play while being idle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* IdleAnimation;

	/** The animation to play while spitting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* SpitAnimation;

	/** The animation to play while throwing eye */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* ThrowEyeAnimation;

	/** The animation to play while dying */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	FVector TeethSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	FVector EyeSpawnLocation;

	void FireTeeth();
	void FireEye();

	void UpdateState();
	void UpdateAnimation();
	void ChangeAnimation(UPaperFlipbook* Animation);

	bool bIsDead = false;
	bool bIsDying = false;
	bool bIsSpitting = false;
	bool bIsThrowingEye = false;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Die() override;

public:
	AGranny();

	virtual void Attack1() override;
	virtual void Attack2() override;
};
