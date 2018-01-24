/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "Appliance.h"

AAppliance::AAppliance() {}

void AAppliance::Hack() {
	if (!bActive) {
		return;
	}

	bActive = false;

	OnHacked();
}

