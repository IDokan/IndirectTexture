// Fill out your copyright notice in the Description page of Project Settings.


#include "IndirectTexture.h"

UIndirectTexture::UIndirectTexture()
	:IndirectTexture(nullptr), TilesetTilesCount(1), IndirectTextureResolution(1)
{
}

void UIndirectTexture::CreateIndirectTexture()
{
	IndirectTexture = UTexture2D::CreateTransient(IndirectTextureResolution.X, IndirectTextureResolution.Y);
	if (IndirectTexture == nullptr)
	{
		return;
	}
	IndirectTexture->AddToRoot();
	IndirectTexture->Filter = TextureFilter::TF_Nearest;

	FTexture2DMipMap& Mip = IndirectTexture->PlatformData->Mips[0];
	void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
	if (Data == nullptr)
	{
		return;
	}
	FColor* ColorData = static_cast<FColor*>(Data);

	for (int32 y = 0; y < IndirectTextureResolution.Y; y++)
	{
		for (int32 x = 0; x < IndirectTextureResolution.X; x++)
		{
			int32 CurrentPixelIndex = (y * IndirectTextureResolution.X) + x;
			int32 TileIndex = FMath::RandRange(0, TilesetTilesCount);
			ColorData[CurrentPixelIndex] = FColor(TileIndex, TileIndex, TileIndex);
		}
	}

	Mip.BulkData.Unlock();
	IndirectTexture->UpdateResource();
}
