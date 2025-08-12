#include "Input/PlayerInputBinderComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interface/PlayerCommand.h"

UPlayerInputBinderComponent::UPlayerInputBinderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerInputBinderComponent::BeginPlay()
{
	Super::BeginPlay();
	BindEnhancedInput();
}

void UPlayerInputBinderComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnbindEnhancedInput();
	Super::EndPlay(EndPlayReason);
}

void UPlayerInputBinderComponent::BindEnhancedInput()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	if (!PC) return;

	if (ULocalPlayer* LP = PC->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsys = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (DefaultMapping)
			{
				Subsys->AddMappingContext(DefaultMapping, 1);
			}
		}
	}

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PC->InputComponent))
	{
		if (IA_Move)
		{
			EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &UPlayerInputBinderComponent::OnMove);
		}
		if (IA_Dash)
		{
			EIC->BindAction(IA_Dash, ETriggerEvent::Started, this, &UPlayerInputBinderComponent::OnDash);
		}
	}
}

void UPlayerInputBinderComponent::UnbindEnhancedInput()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	if (!PC) return;

	if (ULocalPlayer* LP = PC->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsys = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (DefaultMapping)
			{
				Subsys->RemoveMappingContext(DefaultMapping);
			}
		}
	}
}

void UPlayerInputBinderComponent::OnMove(const FInputActionValue& Value)
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	if (!PC) return;

	if (APawn* Pawn = PC->GetPawn())
	{
		if (IPlayerCommand* Command = Cast<IPlayerCommand>(Pawn))
		{
			Command->Cmd_MoveAxis(Value.Get<FVector2D>());
		}
	}
}

void UPlayerInputBinderComponent::OnDash(const FInputActionValue& Value)
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	if (!PC) return;

	if (APawn* Pawn = PC->GetPawn())
	{
		if (IPlayerCommand* Command = Cast<IPlayerCommand>(Pawn))
		{
			Command->Cmd_Dash();
		}
	}
}
