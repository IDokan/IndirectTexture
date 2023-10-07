// Fill out your copyright notice in the Description page of Project Settings.


#include "UMaterialExpressionIndirectTextureSample.h"
#include "MaterialCompiler.h"
#include "MaterialExpressionIO.h"

UMaterialExpressionIndirectTextureSample::UMaterialExpressionIndirectTextureSample()
    :TilesetTexture(nullptr)
{
    TileIndexInput.InputName = TEXT("Result of IndirectTextureObject");
    UVInput.InputName = TEXT("Texture Coordinates");
    TilesetTilesCountInput.InputName = TEXT("Tileset Tiles Count");
    IndirectTextureResolutionInput.InputName = TEXT("Indirect Texture Resolution");
}

TArray<FExpressionOutput>& UMaterialExpressionIndirectTextureSample::GetOutputs()
{
	Outputs.Reset();
	Outputs.Add(RGBOutput);
	return Outputs;
}

int32 UMaterialExpressionIndirectTextureSample::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex)
{
    if (TilesetTexture == nullptr)
    {
        return Compiler->Errorf(TEXT("Indirect Texture is nullptr!"));
    }

    
    if (!TileIndexInput.Expression || !UVInput.Expression || !TilesetTilesCountInput.Expression || !IndirectTextureResolutionInput.Expression)
    {
        return Compiler->Errorf(TEXT("All input should be linked."));
    }
    
    /// <summary>
    /// Calculate size of unit tile of tileset texture
    /// </summary>
    int32 TilesetTilesCount = TilesetTilesCountInput.Compile(Compiler);
    return Compiler->Div(Compiler->Power(TilesetTilesCount, 2.2), Compiler->Constant(4.f));
    int32 TilesetTilesColumnNum = Compiler->ComponentMask(TilesetTilesCount, 1, 0, 0, 0);
    int32 MaxTilesCount = Compiler->Mul(TilesetTilesColumnNum, Compiler->ComponentMask(TilesetTilesCount, 0, 1, 0, 0));
    int32 TileIndex = Compiler->Mul(TileIndexInput.Compile(Compiler), MaxTilesCount);
    //return Compiler->Div(Compiler->Mul(TilesetTilesCount, Compiler->Constant(255.f)), MaxTilesCount);

    int32 X = Compiler->Fmod(TileIndex, TilesetTilesColumnNum);
    int32 Y = Compiler->Div(
        Compiler->Sub(TileIndex, X)
        , TilesetTilesColumnNum);

    return Compiler->Mul(Compiler->Div(Compiler->Add(Compiler->ComponentMask(X, 1, 0, 0, 0), Compiler->ComponentMask(Y, 0, 1, 0, 0)), MaxTilesCount), Compiler->Constant(255.f));
    
    int32 TileSteps = Compiler->Div(Compiler->Constant(1.f), TilesetTilesCount);

    int32 TileColumn = Compiler->Mul(X, Compiler->ComponentMask(TileSteps, 1, 0, 0, 0));
    int32 TileRow = Compiler->Mul(Y, Compiler->ComponentMask(TileSteps, 0, 1, 0, 0));

    /// <summary>
    /// Calculate UV in tileset texture
    /// </summary>
    int32 IndirectTextureResolution = IndirectTextureResolutionInput.Compile(Compiler);
    int32 UV = UVInput.Compile(Compiler);
    
    int32 UVOffsetInIndirectTexture = Compiler->Fmod(UV, Compiler->Div(Compiler->Constant(1.f), IndirectTextureResolution));
    int32 UVOffset = Compiler->Mul(Compiler->Mul(UVOffsetInIndirectTexture, IndirectTextureResolution), TileSteps);

    
    int32 IndirectUV = 
        Compiler->Add(Compiler->Add(Compiler->ComponentMask(TileColumn, 0, 1, 0, 0), Compiler->ComponentMask(TileRow, 0, 0, 1, 0)),
            UVOffset
            );

    int32 TilesetTextureReferenceIndex = Compiler->Texture(TilesetTexture, EMaterialSamplerType::SAMPLERTYPE_Color);
    return IndirectUV;
    return Compiler->TextureSample(TilesetTextureReferenceIndex, IndirectUV, EMaterialSamplerType::SAMPLERTYPE_Color);
}

UTexture* UMaterialExpressionIndirectTextureSample::GetReferencedTexture() const
{
    if (TilesetTexture != nullptr)
    {
        return TilesetTexture;
    }

    return nullptr;
}

bool UMaterialExpressionIndirectTextureSample::CanReferenceTexture() const
{
    return TilesetTexture != nullptr;
}
