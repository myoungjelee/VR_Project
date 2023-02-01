// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <HeadMountedDisplayTypes.h>
#include "VR_Player.generated.h"

UCLASS()
class VR_PROJECT_API AVR_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVR_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere, Category = "VR_Settings | Components")
		class UMotionControllerComponent* motionControllerLeft;
	UPROPERTY(EditAnywhere, Category = "VR_Settings | Components")
		class UMotionControllerComponent* motionControllerRight;
	UPROPERTY(EditAnywhere, Category = "VR_Settings | Components")
		class UCameraComponent* camera;
	UPROPERTY(EditAnywhere, Category = "VR_Settings | Components")
		class UStaticMeshComponent* headMesh;
	UPROPERTY(EditAnywhere, Category = "VR_Settings | Components")
		class UStaticMeshComponent* leftMesh;
	UPROPERTY(EditAnywhere, Category = "VR_Settings | Components")
		class UStaticMeshComponent* rightMesh;
	UPROPERTY(EditAnywhere, Category = "VR_Settings | Components")
		class UTextRenderComponent* leftLog;
	UPROPERTY(EditAnywhere, Category = "VR_Settings | Components")
		class UTextRenderComponent* rightLog;

public:

	UPROPERTY(EditAnywhere, Category = "VR_Settings | ModuleSetting")
		TEnumAsByte<enum EHMDTrackingOrigin::Type> trackOrigin;

private:

	void OnTriggerLeft();
	void OnGripLeft();
	void OnTriggerTouchLeft();
	void OnThumbstickTouchLeft();
	void Horizontal_Left(float value);
	void Vertical_Left(float value);
};
