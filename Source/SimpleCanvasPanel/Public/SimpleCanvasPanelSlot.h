#pragma once

#include "Components/PanelSlot.h"
#include "Widgets/SCanvas.h"

#include "SimpleCanvasPanelSlot.generated.h"

UCLASS()
class SIMPLECANVASPANEL_API USimpleCanvasPanelSlot : public UPanelSlot
{
	GENERATED_BODY()

	UPROPERTY()
	FVector2D Position = FVector2D::ZeroVector;

	UPROPERTY()
	FVector2D Size = FVector2D::UnitVector;

	UPROPERTY()
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = HAlign_Left;

	UPROPERTY()
	TEnumAsByte<EVerticalAlignment> VerticalAlignment = VAlign_Top;

protected:
	virtual void SynchronizeProperties() override;

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

public:
	/** Sets the position of the slot */
	UFUNCTION(BlueprintCallable, Category = "Layout|Simple Canvas Slot")
	void SetPosition(const FVector2D& InPosition);

	/** Gets the position of the slot */
	UFUNCTION(BlueprintCallable, Category = "Layout|Simple Canvas Slot")
	FVector2D GetPosition() const;

	/** Sets the size of the slot */
	UFUNCTION(BlueprintCallable, Category = "Layout|Simple Canvas Slot")
	void SetSize(const FVector2D& InSize);

	/** Gets the size of the slot */
	UFUNCTION(BlueprintCallable, Category = "Layout|Simple Canvas Slot")
	FVector2D GetSize() const;

	UFUNCTION(BlueprintCallable, Category = "Layout|Simple Canvas Slot")
	void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);

	UFUNCTION(BlueprintCallable, Category = "Layout|Simple Canvas Slot")
	EHorizontalAlignment GetHorizontalAlignment() const;

	UFUNCTION(BlueprintCallable, Category = "Layout|Simple Canvas Slot")
	void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);

	UFUNCTION(BlueprintCallable, Category = "Layout|Simple Canvas Slot")
	EVerticalAlignment GetVerticalAlignment() const;

	void BuildSlot(const TSharedRef<SCanvas>& Canvas);

private:
	SCanvas::FSlot* Slot = nullptr;
};
