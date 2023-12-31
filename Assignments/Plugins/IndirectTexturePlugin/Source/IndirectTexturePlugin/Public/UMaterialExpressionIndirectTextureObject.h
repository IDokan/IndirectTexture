// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpression.h"
#include "IndirectTexture.h"
#include "UMaterialExpressionIndirectTextureObject.generated.h"

/**
 * 
 */
UCLASS()
class INDIRECTTEXTUREPLUGIN_API UMaterialExpressionIndirectTextureObject : public UMaterialExpression
{
	GENERATED_BODY()

	UMaterialExpressionIndirectTextureObject();
	virtual TArray<FExpressionOutput>& GetOutputs() override;
	virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;
	virtual UTexture* GetReferencedTexture() const override;
	virtual bool CanReferenceTexture() const override;
	virtual FText GetCreationName() const override;
public:

	UPROPERTY(meta = (RequiredInput = "true"), EditAnywhere, BlueprintReadWrite, Category = "IndirectTexture")
	UIndirectTexture* IndirectTexture;

	UPROPERTY(meta = (RequiredInput = "true"), EditAnywhere, Category = "Indirect Texture")
	FExpressionInput UVInput;

	UPROPERTY()
	FExpressionOutput TileIndexOutput;

	UPROPERTY()
	FExpressionOutput UVOutput;

	UPROPERTY()
	FExpressionOutput TilesetTilesCountOutput;

	UPROPERTY()
	FExpressionOutput IndirectTextureResolutionOutput;
};
