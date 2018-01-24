/*
Roman Borufka, MFF UK, Programmer
Marek Naprstek, FAMU, Graphic and animation artist
Jan Knot, FAMU, Sound designer, music artist
*/

#include "ToastyConquestGameModeBase.h"
#include "Toaster.h"
#include "ToasterController.h"
#include "ToasterHUD.h"

AToastyConquestGameModeBase::AToastyConquestGameModeBase() 
	: Super()
{
	PlayerControllerClass = AToasterController::StaticClass();
	HUDClass = AToasterHUD::StaticClass();
	DefaultPawnClass = AToaster::StaticClass();
}

void AToastyConquestGameModeBase::SetFightMode(bool bFightMode) {
	bFightModeOn = bFightMode;
}

