// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpression.h"
#include "UMaterialExpressionIndirectTextureSample.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENTS_API UMaterialExpressionIndirectTextureSample : public UMaterialExpression
{
	GENERATED_BODY()
	
public:
	virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;
	virtual uint32 GetInputType(int32 InputIndex) override;
	virtual UObject* GetReferencedTexture() const override;
	virtual bool CanReferenceTexture() const override { return true; }
	
public:
	UMaterialExpressionIndirectTextureSample();

	UPROPERTY(meta = (RequiredInput = "true"), EditAnywhere, BlueprintReadWrite, Category = IndirectTexture)
	UTexture* Texture;

	UPROPERTY(meta = (RequiredInput = "true"))
	FExpressionInput TextureObject;

	UPROPERTY(EditAnywhere, Category = IndirectTexture)
	int32 TilesetTilesCount;

	UPROPERTY(EditAnywhere, Category = IndirectTexture)
	FVector2D IndirectTextureResolution;
};
