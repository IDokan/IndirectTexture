// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SLeafWidget.h"

DECLARE_DELEGATE_OneParam(FOnTilesetTilesCountChanged, int32)
DECLARE_DELEGATE_OneParam(FOnIndirectTextureResolutionChanged, FIntPoint)


/**
 * 
 */
class INDIRECTTEXTUREPLUGINEDITOR_API SIndirectTextureWidget : SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SIndirectTextureWidget)
		: _TilesetTilesCount(1), _IndirectTextureResolution(FIntPoint(1))
	{}

	SLATE_ATTRIBUTE(int32, TilesetTilesCount)
		SLATE_ATTRIBUTE(FIntPoint, IndirectTextureResolution)
		SLATE_EVENT(FOnTilesetTilesCountChanged, OnTilesetTilesCountChanged)
		SLATE_EVENT(FOnIndirectTextureResolutionChanged, OnIndirectTextureResolutionChanged)
		SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	FVector2D ComputeDesiredSize(float) const override;

	//FReply OnMouseButtonDown(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent) override;
	FReply OnMouseButtonUp(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent) override;
	FReply OnMouseMove(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent) override;
private:
	TAttribute<int32> TilessetTilesCount;
	TAttribute<FIntPoint> IndirectTextureResolution;

	FOnTilesetTilesCountChanged OnTilesetTilesCountChanged;
	FOnIndirectTextureResolutionChanged OnIndirectTextureResolutionChanged;
};
