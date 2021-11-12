#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEndedEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBL_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	int StartHealth;
protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(int fix);

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthEndedEvent OnHealthEnded;

		
};
