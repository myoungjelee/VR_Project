// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Player.h"
#include <MotionControllerComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <HeadMountedDisplayFunctionLibrary.h>
#include <Components/TextRenderComponent.h>

// Sets default values
AVR_Player::AVR_Player()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetupAttachment(RootComponent);
	headMesh = CreateDefaultSubobject<UStaticMeshComponent>("HeadMesh");
	headMesh->SetupAttachment(camera);
	headMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	motionControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeft"));
	motionControllerLeft->SetupAttachment(RootComponent);
	motionControllerLeft->MotionSource = "Left";

	leftMesh = CreateDefaultSubobject<UStaticMeshComponent>("LeftMesh");
	leftMesh->SetupAttachment(motionControllerLeft);
	leftMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	leftLog = CreateDefaultSubobject<UTextRenderComponent>("Left Log Text");
	leftLog->SetupAttachment(motionControllerLeft);
	leftLog->SetRelativeRotation(FRotator(0, 180, 0));
	leftLog->SetTextRenderColor(FColor::Yellow);
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);

	motionControllerRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRight"));
	motionControllerRight->SetupAttachment(RootComponent);
	motionControllerRight->MotionSource = "Right";

	rightMesh = CreateDefaultSubobject<UStaticMeshComponent>("RightMesh");
	rightMesh->SetupAttachment(motionControllerRight);
	rightMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	rightLog = CreateDefaultSubobject<UTextRenderComponent>("Right Log Text");
	rightLog->SetupAttachment(motionControllerRight);
	rightLog->SetRelativeRotation(FRotator(0, 180, 0));
	rightLog->SetTextRenderColor(FColor::Yellow);
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);
}

// Called when the game starts or when spawned
void AVR_Player::BeginPlay()
{
	Super::BeginPlay();

	//헤드 장비의 기준 위치를 설정한다.
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(trackOrigin.GetValue());
	}
}

// Called every frame
void AVR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TriggerLeft", IE_Pressed, this, &AVR_Player::OnTriggerLeft);
	PlayerInputComponent->BindAction("GripLeft", IE_Pressed, this, &AVR_Player::OnGripLeft);
	PlayerInputComponent->BindAction("TriggerTouchLeft", IE_Pressed, this, &AVR_Player::OnTriggerTouchLeft);
	PlayerInputComponent->BindAction("ThumbstickTouchLeft", IE_Pressed, this, &AVR_Player::OnThumbstickTouchLeft);

	PlayerInputComponent->BindAxis("ThumbstickHorizontal", this, &AVR_Player::Horizontal_Left);
	PlayerInputComponent->BindAxis("ThumbstickVertical", this, &AVR_Player::Vertical_Left);
}




void AVR_Player::OnTriggerLeft()
{
	leftLog->SetText(FText::FromString(__FUNCTION__));
}

void AVR_Player::OnGripLeft()
{
	leftLog->SetText(FText::FromString(__FUNCTION__));
}

void AVR_Player::OnTriggerTouchLeft()
{
	leftLog->SetText(FText::FromString(__FUNCTION__));
}

void AVR_Player::OnThumbstickTouchLeft()
{
	leftLog->SetText(FText::FromString(__FUNCTION__));
}

void AVR_Player::Horizontal_Left(float value)
{
	FString msg = FString::Printf(TEXT("%.3f, "), value);
	//FString result = leftLog->Text.ToString() + msg;
	leftLog->SetText(FText::FromString(msg));
}

void AVR_Player::Vertical_Left(float value)
{
	FString msg = FString::Printf(TEXT("%.3f"), value);
	FString result = leftLog->Text.ToString() + msg;
	leftLog->SetText(FText::FromString(result));
}

