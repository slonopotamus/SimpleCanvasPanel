#pragma once

#include "Components/PanelWidget.h"

#include "SimpleCanvasPanel.generated.h"

class USimpleCanvasPanelSlot;
class SCanvas;

UCLASS()
class SIMPLECANVASPANEL_API USimpleCanvasPanel : public UPanelWidget
{
	GENERATED_BODY()

protected:
	USimpleCanvasPanel();

	TSharedPtr<SCanvas> MyCanvas;

	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual UClass* GetSlotClass() const override;

	virtual void OnSlotAdded(UPanelSlot* InSlot) override;

	virtual void OnSlotRemoved(UPanelSlot* InSlot) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Simple Canvas Panel")
	USimpleCanvasPanelSlot* AddChildToCanvas(UWidget* Content);

	/** Gets the underlying native canvas widget if it has been constructed */
	TSharedPtr<SCanvas> GetCanvasWidget() const;

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;

	virtual bool LockToPanelOnDrag() const override
	{
		return true;
	}
#endif
};
