// Fill out your copyright notice in the Description page of Project Settings.


#include "SIndirectTextureWidget.h"
#include "Editor.h"

void SIndirectTextureWidget::Construct(const FArguments& InArgs)
{
	TilessetTilesCount = InArgs._TilesetTilesCount;
	IndirectTextureResolution = InArgs._IndirectTextureResolution;

	OnTilesetTilesCountChanged = InArgs._OnTilesetTilesCountChanged;
	OnIndirectTextureResolutionChanged = InArgs._OnIndirectTextureResolutionChanged;
}

int32 SIndirectTextureWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	// May I draw a texture on here?
	TArray<FVector2D> Points;
	Points.Add(FVector2D(0.f));
	FSlateDrawElement::MakeLines(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), Points);
	return LayerId;
}

FVector2D SIndirectTextureWidget::ComputeDesiredSize(float) const
{
	return FVector2D(200.f, 200.f);
}

//FReply SIndirectTextureWidget::OnMouseButtonDown(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent)
//{
//	if (GEditor && ensure(!GIsTransacting))
//	{
//		GEditor->BeginTransaction(TEXT(""), INVTEXT("Edit Indirect Texture"), nullptr);
//	}
//
//	return FReply::Handled().CaptureMouse(SharedThis(this));
//}

FReply SIndirectTextureWidget::OnMouseButtonUp(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent)
{
	if (GEditor)
	{
		GEditor->EndTransaction();
	}
	return FReply::Handled().ReleaseMouseCapture();
}

FReply SIndirectTextureWidget::OnMouseMove(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent)
{
	if (!HasMouseCapture())
	{
		return FReply::Unhandled();
	}

	return FReply::Handled();
}
