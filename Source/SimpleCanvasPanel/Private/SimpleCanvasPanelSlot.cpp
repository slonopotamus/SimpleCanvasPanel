#include "SimpleCanvasPanelSlot.h"

#include "Components/Widget.h"

void USimpleCanvasPanelSlot::SetPosition(const FVector2D& InPosition)
{
	Position = InPosition;
	if (Slot)
	{
		Slot->SetPosition(Position);
	}
}

FVector2D USimpleCanvasPanelSlot::GetPosition() const
{
	return Slot ? Slot->GetPosition() : Position;
}

void USimpleCanvasPanelSlot::SetSize(const FVector2D& InSize)
{
	Size = InSize;
	if (Slot)
	{
		Slot->SetSize(Size);
	}
}

FVector2D USimpleCanvasPanelSlot::GetSize() const
{
	return Slot ? Slot->GetSize() : Size;
}

void USimpleCanvasPanelSlot::SetHorizontalAlignment(const EHorizontalAlignment InHorizontalAlignment)
{
	HorizontalAlignment = InHorizontalAlignment;
	if (Slot)
	{
		Slot->SetHorizontalAlignment(HorizontalAlignment);
	}
}

EHorizontalAlignment USimpleCanvasPanelSlot::GetHorizontalAlignment() const
{
	if (Slot)
	{
		return Slot->GetHorizontalAlignment();
	}
	return HorizontalAlignment;
}

void USimpleCanvasPanelSlot::SetVerticalAlignment(const EVerticalAlignment InVerticalAlignment)
{
	VerticalAlignment = InVerticalAlignment;
	if (Slot)
	{
		Slot->SetVerticalAlignment(InVerticalAlignment);
	}
}

EVerticalAlignment USimpleCanvasPanelSlot::GetVerticalAlignment() const
{
	if (Slot)
	{
		return Slot->GetVerticalAlignment();
	}
	return VerticalAlignment;
}

void USimpleCanvasPanelSlot::BuildSlot(const TSharedRef<SCanvas>& Canvas)
{
	Canvas->AddSlot()
	    .Expose(Slot)
	        [Content == nullptr ? SNullWidget::NullWidget : Content->TakeWidget()];

	SynchronizeProperties();
}

void USimpleCanvasPanelSlot::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	SetPosition(Position);
	SetSize(Size);
	SetHorizontalAlignment(HorizontalAlignment);
	SetVerticalAlignment(VerticalAlignment);
}

void USimpleCanvasPanelSlot::ReleaseSlateResources(const bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Slot = nullptr;
}
