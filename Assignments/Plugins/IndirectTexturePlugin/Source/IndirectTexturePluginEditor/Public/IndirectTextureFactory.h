// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "IndirectTextureFactory.generated.h"

/**
 * 
 */
UCLASS()
class INDIRECTTEXTUREPLUGINEDITOR_API UIndirectTextureFactory : public UFactory
{
	GENERATED_BODY()

public:
	UIndirectTextureFactory();
	UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);
};
