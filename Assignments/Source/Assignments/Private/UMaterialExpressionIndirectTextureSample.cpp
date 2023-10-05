// Fill out your copyright notice in the Description page of Project Settings.


#include "UMaterialExpressionIndirectTextureSample.h"
#include "MaterialCompiler.h"
#include "MaterialExpressionIO.h"

uint32 UMaterialExpressionIndirectTextureSample::GetInputType(int32 InputIndex)
{
	return uint32();
}

UObject* UMaterialExpressionIndirectTextureSample::GetReferencedTexture() const
{
	return nullptr;
}

UMaterialExpressionIndirectTextureSample::UMaterialExpressionIndirectTextureSample()
{
	TilesetTilesCount = 0;
	
	IndirectTextureResolution = FVector2D(0, 0);

	Outputs.Add(FExpressionOutput(TEXT("Output")));
	Outputs.Add(FExpressionOutput(TEXT("1")));
	Outputs.Add(FExpressionOutput(TEXT("2")));
	Outputs.Add(FExpressionOutput(TEXT("3")));
	Outputs.Add(FExpressionOutput(TEXT("4")));
}

int32 UMaterialExpressionIndirectTextureSample::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex)
{
	return Compiler->Constant(TilesetTilesCount);
}