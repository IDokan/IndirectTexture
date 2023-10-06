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
	switch (OutputIndex)
	{
	case 1:
		return UVInput.Compile(Compiler);
		break;
	case 2:
		return Compiler->Constant(IndirectTexture->TilesetTilesCount);
		break;
	case 3:
		return Compiler->Constant2(IndirectTexture->IndirectTextureResolution.X, IndirectTexture->IndirectTextureResolution.Y);
		break;
	default:
		break;
	}

	if (IndirectTexture == nullptr || IndirectTexture->IndirectTexture == nullptr)
	{
		return Compiler->Errorf(TEXT("Indirect Texture is nullptr!"));
	}

	int32 IndirectTextureTextureReferenceIndex = Compiler->Texture(IndirectTexture->IndirectTexture, EMaterialSamplerType::SAMPLERTYPE_Grayscale);

	int32 UVs = Compiler->TextureCoordinate(0, false, false);

	return Compiler->TextureSample(IndirectTextureTextureReferenceIndex, UVs, EMaterialSamplerType::SAMPLERTYPE_Color);
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
