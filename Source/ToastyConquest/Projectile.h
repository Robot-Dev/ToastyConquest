/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UPaperFlipbookComponent;
class UProjectileMovementComponent;
class USoundCue;

/**
*
*/
UCLASS()
class TOASTYCONQUEST_API AProjectile : public AActor
{
	GENERATED_BODY()
	
protected:
	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;

	/** Sprite component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* Sprite;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	/** The damage of the toast dealt to enemies */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
	float Damage = 1.0f;

	/** Begin Play */
	virtual void BeginPlay() override;

	/** Overlap and Hit Methods */
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) PURE_VIRTUAL(AProjectile::OnOverlapBegin,);

public:
	AProjectile();

	/** Returns whether the toaster can climb **/
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
