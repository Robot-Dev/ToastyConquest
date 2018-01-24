/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "Animal.h"


AAnimal::AAnimal() {}

void AAnimal::TakeDamage(float Damage) {
	Health -= Damage;
	if (Health <= 0) {
		Destroy();
	}
}