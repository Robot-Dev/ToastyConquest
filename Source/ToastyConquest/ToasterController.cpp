/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "ToasterController.h"

#include "Toaster.h"

void AToasterController::BeginPlay() {
	Super::BeginPlay();
	APawn* Pawn = GetPawn();
	if (Pawn) {
		Possess(Pawn);
	}
}

void AToasterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent) {
		InputComponent->BindAxis("Move Right", this, &AToasterController::MoveRight);
		InputComponent->BindAxis("Climb", this, &AToasterController::Climb);
		InputComponent->BindAction("Jump", IE_Pressed, this, &AToasterController::Jump); 
		InputComponent->BindAction("Fire", IE_Pressed, this, &AToasterController::StartFire);
		InputComponent->BindAction("Fire", IE_Released, this, &AToasterController::Fire);
		InputComponent->BindAction("Hack", IE_Pressed, this, &AToasterController::Hack);
	}
}

// Input

void AToasterController::MoveRight(float Value) {
	AToaster* Player = Cast<AToaster>(GetPawn());
	if (Player) {
		Player->MoveRight(Value);
	}
}

void AToasterController::Jump() {
	AToaster* Player = Cast<AToaster>(GetPawn());
	if (Player) {
		if (!Player->CanClimb()) {
			Player->Jump();
		}
	}
}

void AToasterController::Climb(float Value) {
	AToaster* Player = Cast<AToaster>(GetPawn());
	if (Player) {
		if (Player->CanClimb()) {
			Player->Climb(Value);
		}
	}
}

void AToasterController::StartFire() {
	AToaster* Player = Cast<AToaster>(GetPawn());
	if (Player) {
		Player->StartFire();
	}
}

void AToasterController::Fire() {
	AToaster* Player = Cast<AToaster>(GetPawn());
	if (Player) {
		Player->Fire();
	}
}

void AToasterController::Hack() {
	AToaster* Player = Cast<AToaster>(GetPawn());
	if (Player) {
		Player->Hack();
	}
}

