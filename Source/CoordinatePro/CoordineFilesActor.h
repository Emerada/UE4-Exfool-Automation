// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoordineFilesActor.generated.h"

UCLASS()
class COORDINATEPRO_API ACoordineFilesActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoordineFilesActor();

	//UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString CategoryPath;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InitCoordineFilesInsv(FString FloderAddress);

	UFUNCTION(BlueprintCallable)
	void InitCoordineFilesMp4(FString FloderAddress);

	float AddUECommondAddress(FString UECommondAddress,float Number);

	void CreateFile(FString UEFileAddress);

};
