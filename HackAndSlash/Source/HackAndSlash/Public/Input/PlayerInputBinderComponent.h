#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "PlayerInputBinderComponent.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKANDSLASH_API UPlayerInputBinderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerInputBinderComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Dash;


public:
	void BindEnhancedInput();
	void UnbindEnhancedInput();

	void OnMove(const FInputActionValue& Value);
	void OnDash(const FInputActionValue& Value);	
};
