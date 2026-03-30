#include "MySpartaSpeechBubbleWidgetBase.h"
#include "Components/TextBlock.h"
#include "Fonts/SlateFontInfo.h"

void UMySpartaSpeechBubbleWidgetBase::SetSpeechText(const FText& InText)
{
	CurrentSpeechText = InText;

	if (Text_Message)
	{
		Text_Message->SetText(InText);
	}

	BP_OnSpeechUpdated(CurrentSpeechText, CurrentTextColor, CurrentFontSize);
}

void UMySpartaSpeechBubbleWidgetBase::SetSpeechTextColor(const FLinearColor& InColor)
{
	CurrentTextColor = InColor;

	if (Text_Message)
	{
		Text_Message->SetColorAndOpacity(FSlateColor(InColor));
	}

	BP_OnSpeechUpdated(CurrentSpeechText, CurrentTextColor, CurrentFontSize);
}

void UMySpartaSpeechBubbleWidgetBase::SetSpeechFontSize(int32 InFontSize)
{
	CurrentFontSize = InFontSize;

	if (Text_Message)
	{
		FSlateFontInfo FontInfo = Text_Message->GetFont();
		FontInfo.Size = InFontSize;
		Text_Message->SetFont(FontInfo);
	}

	BP_OnSpeechUpdated(CurrentSpeechText, CurrentTextColor, CurrentFontSize);
}