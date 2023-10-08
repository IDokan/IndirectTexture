// Fill out your copyright notice in the Description page of Project Settings.


#include "UMaterialExpressionIndirectTextureObject.h"
#include "MaterialCompiler.h"

UMaterialExpressionIndirectTextureObject::UMaterialExpressionIndirectTextureObject()
{

}

TArray<FExpressionOutput>& UMaterialExpressionIndirectTextureObject::GetOutputs()
{
	// TODO: insert return statement here
	Outputs.Reset();
	Outputs.Add(RGBOutput);
	Outputs.Add(UVOutput);
	Outputs.Add(TilesetTilesCountOutput);
	Outputs.Add(IndirectTextureResolutionOutput);
	return Outputs;
}

int32 UMaterialExpressionIndirectTextureObject::Compile(FMaterialCompiler* Compiler, int32 OutputIndex)
{
	if (UVInput.Expression == nullptr || IndirectTexture == nullptr || IndirectTexture->IndirectTexture == nullptr)
	{
		return Compiler->Errorf(TEXT("Indirect Texture is nullptr!"));
	}

	switch (OutputIndex)
	{
	case 1:
		return UVInput.Compile(Compiler);
		break;
	case 2:
		return Compiler->Constant2(IndirectTexture->TilesetTilesCount.X, IndirectTexture->TilesetTilesCount.Y);
		break;
	case 3:
		return Compiler->Constant2(IndirectTexture->IndirectTextureResolution.X, IndirectTexture->IndirectTextureResolution.Y);
		break;
	default:
		break;
	}

	int32 IndirectTextureTextureReferenceIndex = Compiler->Texture(IndirectTexture->IndirectTexture, EMaterialSamplerType::SAMPLERTYPE_Data);

	int32 UVs = UVInput.Compile(Compiler);

	return Compiler->TextureSample(IndirectTextureTextureReferenceIndex, UVs, EMaterialSamplerType::SAMPLERTYPE_Data);
}

UTexture* UMaterialExpressionIndirectTextureObject::GetReferencedTexture() const
{
	if (IndirectTexture != nullptr)
	{
		if (IndirectTexture->IndirectTexture != nullptr)
		{
			return IndirectTexture->IndirectTexture;
		}
	}

	return nullptr;
}

bool UMaterialExpressionIndirectTextureObject::CanReferenceTexture() const
{
	return IndirectTexture != nullptr && IndirectTexture->IndirectTexture != nullptr;
}
