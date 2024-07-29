#include "SimpleCanvasPanel.h"

#include "SimpleCanvasPanelSlot.h"
#include "Widgets/SCanvas.h"

USimpleCanvasPanel::USimpleCanvasPanel()
{
	bIsVariable = false;
	SetVisibilityInternal(ESlateVisibility::SelfHitTestInvisible);
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

void USimpleCanvasPanel::OnSlotAdded(UPanelSlot* Slot)
{
	if (MyCanvas)
	{
		CastChecked<USimpleCanvasPanelSlot>(Slot)->BuildSlot(MyCanvas.ToSharedRef());
	}
}

void USimpleCanvasPanel::OnSlotRemoved(UPanelSlot* Slot)
{
	if (MyCanvas && Slot->Content)
	{
		if (const auto Widget = Slot->Content->GetCachedWidget())
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
