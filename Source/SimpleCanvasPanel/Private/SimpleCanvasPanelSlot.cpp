#include "SimpleCanvasPanelSlot.h"
#include "Components/Widget.h"

void USimpleCanvasPanelSlot::SetPosition(const FVector2D& InPosition)
{
	Position = InPosition;
	if (Slot)
	{
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
		Slot->SetPosition(Position);
#else
		Slot->Position(Position);
#endif
	}
}

FVector2D USimpleCanvasPanelSlot::GetPosition() const
{
	if (Slot)
	{
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
		return Slot->GetPosition();
#else
		return Slot->PositionAttr.Get();
#endif
	}

	return Position;
}

void USimpleCanvasPanelSlot::SetSize(const FVector2D& InSize)
{
	Size = InSize;
	if (Slot)
	{
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
		Slot->SetSize(Size);
#else
		Slot->Size(InSize);
#endif
	}
}

FVector2D USimpleCanvasPanelSlot::GetSize() const
{
	if (Slot)
	{
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
		return Slot->GetSize();
#else
		return Slot->SizeAttr.Get();
#endif
	}

	return Size;
}

void USimpleCanvasPanelSlot::SetHorizontalAlignment(const EHorizontalAlignment InHorizontalAlignment)
{
	HorizontalAlignment = InHorizontalAlignment;
	if (Slot)
	{
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
		Slot->SetHorizontalAlignment(HorizontalAlignment);
#else
		Slot->HAlign(HorizontalAlignment);
#endif
	}
}

EHorizontalAlignment USimpleCanvasPanelSlot::GetHorizontalAlignment() const
{
	if (Slot)
	{
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
		return Slot->GetHorizontalAlignment();
#else
		return Slot->HAlignment;
#endif
	}

	return HorizontalAlignment;
}

void USimpleCanvasPanelSlot::SetVerticalAlignment(const EVerticalAlignment InVerticalAlignment)
{
	VerticalAlignment = InVerticalAlignment;
	if (Slot)
	{
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
		Slot->SetVerticalAlignment(InVerticalAlignment);
#else
		Slot->VAlign(InVerticalAlignment);
#endif
	}
}

EVerticalAlignment USimpleCanvasPanelSlot::GetVerticalAlignment() const
{
	if (Slot)
	{
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
		return Slot->GetVerticalAlignment();
#else
		return Slot->VAlignment;
#endif
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
