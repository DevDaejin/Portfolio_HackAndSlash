#include "Modes/BasicPlayerController.h"
#include "Input/PlayerInputBinderComponent.h"

ABasicPlayerController::ABasicPlayerController()
{
	InputBinder = CreateDefaultSubobject<UPlayerInputBinderComponent>(TEXT("InputBinder"));
}
