#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

class UPlayerInputBinderComponent;

UCLASS()
class HACKANDSLASH_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasicPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPlayerInputBinderComponent> InputBinder;
};
