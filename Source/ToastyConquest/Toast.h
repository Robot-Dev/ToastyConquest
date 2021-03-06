/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "FriendlyProjectile.h"
#include "Toast.generated.h"

class UPaperFlipbook;

/**
*
*/
UCLASS()
class TOASTYCONQUEST_API AToast : public AFriendlyProjectile
{
	GENERATED_BODY()
	
protected:
/** Sounds */
	/** The sound to play when exploded */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	USoundCue* ToastExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* ToastExplosionAnimation;

	FTimerHandle ToastExplosionHandle;

	/** Begin Play and Tick*/
	virtual void BeginPlay() override;

	/** Other Methods */
	UFUNCTION(BlueprintCallable, Category = "Events")
	void Explode();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnExplode();

protected:
	/** Overlap and Hit Methods */
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;

public:
	AToast();
};
