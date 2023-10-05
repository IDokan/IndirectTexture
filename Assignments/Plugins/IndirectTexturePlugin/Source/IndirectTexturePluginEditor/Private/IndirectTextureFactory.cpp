// Fill out your copyright notice in the Description page of Project Settings.


#include "IndirectTextureFactory.h"

#include "IndirectTextureFactory.h"
#include "IndirectTexture.h"

UIndirectTextureFactory::UIndirectTextureFactory()
{
	SupportedClass = UIndirectTexture::StaticClass();
	bCreateNew = true;
}

UObject* UIndirectTextureFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UIndirectTexture>(InParent, Class, Name, Flags, Context);
}
