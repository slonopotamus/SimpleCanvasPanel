#include "SimpleCanvasPanel.h"
#include "SimpleCanvasPanelSlot.h"
#include "Widgets/SCanvas.h"

USimpleCanvasPanel::USimpleCanvasPanel()
{
	bIsVariable = false;

#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1)
	SetVisibilityInternal(ESlateVisibility::SelfHitTestInvisible);
#else
	Visibility = ESlateVisibility::SelfHitTestInvisible;
#endif
}

void USimpleCanvasPanel::ReleaseSlateResources(const bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyCanvas.Reset();
}

UClass* USimpleCanvasPanel::GetSlotClass() const
{
	return USimpleCanvasPanelSlot::StaticClass();
}

void USimpleCanvasPanel::OnSlotAdded(UPanelSlot* InSlot)
{
	if (MyCanvas)
	{
		CastChecked<USimpleCanvasPanelSlot>(InSlot)->BuildSlot(MyCanvas.ToSharedRef());
	}
}

void USimpleCanvasPanel::OnSlotRemoved(UPanelSlot* InSlot)
{
	if (MyCanvas && InSlot->Content)
	{
		if (const auto Widget = InSlot->Content->GetCachedWidget())
		{
			MyCanvas->RemoveSlot(Widget.ToSharedRef());
		}
	}
}

TSharedRef<SWidget> USimpleCanvasPanel::RebuildWidget()
{
	MyCanvas = SNew(SCanvas);

	for (UPanelSlot* PanelSlot : Slots)
	{
		if (auto* TypedSlot = Cast<USimpleCanvasPanelSlot>(PanelSlot))
		{
			TypedSlot->Parent = this;
			TypedSlot->BuildSlot(MyCanvas.ToSharedRef());
		}
	}

	return MyCanvas.ToSharedRef();
}

USimpleCanvasPanelSlot* USimpleCanvasPanel::AddChildToCanvas(UWidget* Content)
{
	return Cast<USimpleCanvasPanelSlot>(Super::AddChild(Content));
}

TSharedPtr<SCanvas> USimpleCanvasPanel::GetCanvasWidget() const
{
	return MyCanvas;
}

#if WITH_EDITOR

const FText USimpleCanvasPanel::GetPaletteCategory()
{
	return NSLOCTEXT("UMG", "Panel", "Panel");
}

#endif
