#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerCommand.generated.h"

UINTERFACE(MinimalAPI)
class UPlayerCommand : public UInterface
{
	GENERATED_BODY()
};
class IPlayerCommand
{
	GENERATED_BODY()

public:
	virtual void Cmd_MoveAxis(const FVector2D& Axis) = 0;
	virtual void Cmd_Dash() = 0;
};
