/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "PaperCharacter.h"
#include "Human.generated.h"

class USoundCue;
class AToaster;

/**
*
*/
UCLASS()
class TOASTYCONQUEST_API AHuman : public APaperCharacter
{
	GENERATED_BODY()
	
protected:
	/** The sound to play when colliding with toaster */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	USoundCue* KnockBackSound;

	/** The sound to play when damaged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	USoundCue* DamagedSound;

	/** The sound to play when damaged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	USoundCue* DeathSound;

/** Health */
	/** Total health */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float Health = 1.0f;

/** Knock Back */
	/** How far will the toaster be knocked back */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KnockBack, meta = (AllowPrivateAccess = "true"))
	float KnockBackDistance = 500.0f;

/** Begin Play and Tick */
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void UpdateRotation();

/** Overlap and Hit methods */

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

/** Other Methods */
	void KnockBack(AToaster* Toaster);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float Attack1FirstCooldown = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float Attack2FirstCooldown = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float Attack1Cooldown = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float Attack2Cooldown = 1.0f;

	bool bIsInvincible = false;

	FTimerHandle Attack1Handle;
	FTimerHandle Attack2Handle;

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnHurt();

	virtual void Die();

public:
	AHuman();

	virtual void Attack1();
	virtual void Attack2();

	void TakeDamage(float Damage);
};
