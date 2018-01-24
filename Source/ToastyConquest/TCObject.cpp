/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/


#include "TCObject.h"

#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

/** Constructor */

ATCObject::ATCObject() {
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetBoxExtent(FVector(0.0f, 100.0f, 0.0f));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	CollisionComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	RootComponent = CollisionComponent;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Sprite->SetupAttachment(RootComponent);
}
