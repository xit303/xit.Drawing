#include "Drawing/Label.h"

#ifdef DEBUG_LABEL
#include <iostream>
#include <chrono>
#endif

namespace xit::Drawing
{
    Label::Label(int column, int row, int columnSpan, int rowSpan)
    {
        SetInheritForeground(true);
        SetClipToBounds(false);
        SetName("Label");

        SetVerticalAlignment(VerticalAlignment::Center);
        SetGrid(column, row, columnSpan, rowSpan);
    }

    Label::Label(const std::string &text, int column, int row, int columnSpan, int rowSpan)
        : Label(column, row, columnSpan, rowSpan)
    {
        SetText(text);
    }

    void Label::OnTextChanged()
    {
#ifdef DEBUG_LABEL
        std::cout << "[DEBUG] Label::OnTextChanged() called, text='" << GetText() << "' at timestamp " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() << std::endl;
#endif
        TextProperty::SetNeedMeasureText(true);
        FontProperty::SetNeedMeasureFont(true);
#ifdef DEBUG_LABEL
        std::cout << "[DEBUG] About to call Label::Invalidate()" << std::endl;
#endif
        Invalidate();
#ifdef DEBUG_LABEL
        std::cout << "[DEBUG] Label::Invalidate() returned" << std::endl;
#endif
    }

    void Label::OnTextWrappingChanged()
    {
        TextProperty::SetNeedMeasureText(true);
        FontProperty::SetNeedMeasureFont(true);
        Invalidate();
    }

    void Label::OnFontSizeChanged()
    {
        TextProperty::SetNeedMeasureText(true);
        FontProperty::SetNeedMeasureFont(true);
        Invalidate();
    }

    void Label::OnForegroundChanged(EventArgs &e)
    {
        Visual::OnForegroundChanged(e);

        const SolidColorBrush *solidColorBrush = dynamic_cast<const SolidColorBrush *>(GetForeground());
        color = solidColorBrush
                    ? solidColorBrush->GetColor()
                    : vec4(1, 0, 0, 1);
        color.a = solidColorBrush ? solidColorBrush->GetOpacity() : 1.0f;
    }

    int Label::OnMeasureWidth(int available)
    {
        MeasureText();
        return textSize.GetWidth();
    }

    int Label::OnMeasureHeight(int available)
    {
        MeasureText();
        return textSize.GetHeight();
    }

    void Label::OnLayoutCompleted(const Rectangle &bounds)
    {
        Visual::OnLayoutCompleted(bounds);

        if (GetNeedLeftRecalculation() || GetNeedTopRecalculation())
        {
#ifdef DEBUG_LABEL
            int oldTextTop = textTop;
#endif
            // Update textTop based on the current layout and scene height
            // This ensures the text is positioned correctly within the label
            textTop = Scene2D::CurrentScene().GetHeight() - GetTop() - textSize.GetHeight();

#ifdef DEBUG_LABEL
            std::cout << "[DEBUG] Label::OnLayoutCompleted '" << GetName() << "': bounds=" << bounds.GetLeft() << "," << bounds.GetTop() << "," << bounds.GetWidth() << "x" << bounds.GetHeight()
                      << ", GetTop()=" << GetTop() << ", textSize.height=" << textSize.GetHeight()
                      << ", Scene height=" << Scene2D::CurrentScene().GetHeight()
                      << ", textTop changed from " << oldTextTop << " to " << textTop << std::endl;
#endif
        }
    }

    void Label::OnRender()
    {
        std::string text = GetText();

#ifdef DEBUG_LABEL
        std::cout << "[DEBUG] Label::OnRender() called with text='" << text << "' name='" << GetName() << "' at timestamp " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() << std::endl;
        std::cout << "[DEBUG] GetLeft()=" << GetLeft() << ", textTop=" << textTop << ", GetZIndex()=" << GetZIndex() << std::endl;
#endif

        if (!text.empty())
        {
#ifdef DEBUG_LABEL
            std::cout << "[DEBUG] Calling TextRenderer::RenderText()" << std::endl;
#endif
            TextRenderer::RenderText(GetFontName(), GetFontSize(), text, GetLeft(), textTop, GetZIndex(), color);
#ifdef DEBUG_LABEL
            std::cout << "[DEBUG] TextRenderer::RenderText() returned" << std::endl;
#endif
        }
        else
        {
#ifdef DEBUG_LABEL
            std::cout << "[DEBUG] Text is empty, not rendering" << std::endl;
#endif
        }
    }

    void Label::SetDPIScale(float scaleX, float scaleY)
    {
        TextProperty::SetNeedMeasureText(true);
        FontProperty::SetNeedMeasureFont(true);
        Visual::SetDPIScale(scaleX, scaleY);
    }

    Size Label::Measure(const Size &availableSize)
    {
        return Visual::Measure(availableSize);
    }

    Size &Label::MeasureText()
    {
        bool needMeasureText = TextProperty::GetNeedMeasureText() || FontProperty::GetNeedMeasureFont();

        if (needMeasureText && GetIsVisible())
        {
            int scaledFontSize = (int)((float)GetFontSize() * GetScaleX());
            const std::string &thisText = GetText();

            if (thisText.empty())
            {
                // even if empty, we need to reserve the height for the text
                textSize.SetWidth(0);
                textSize.SetHeight(scaledFontSize);
                return textSize;
            }

            MeasureText(GetFontName(), scaledFontSize, thisText, textSize);

            if (!textSize.IsEmpty())
            {
                TextProperty::SetNeedMeasureText(false);
                FontProperty::SetNeedMeasureFont(false);
            }
            else
            {
#ifdef DEBUG_LABEL
                std::cout << "Label::MeasureText: textSize is empty" << std::endl;
#endif
            }
        }
        return textSize;
    }

    const void Label::MeasureText(const std::string &fontName, int fontSize, const std::string &text, Size &target)
    {
        FontStorage::FindOrCreate(fontName, fontSize).Measure(text, target);
    }

    //******************************************************************************
    // #region public static Create Methods
    //******************************************************************************

    Label *Label::CreateHeader(int column, int row, int columnSpan, int rowSpan)
    {
        Label *l = new Label(column, row, columnSpan, rowSpan);
        l->SetBrushGroup("Header");
        l->SetLayoutGroup("HeaderText");
        return l;
    }

    Label *Label::CreateHeader(const std::string &text, int column, int row, int columnSpan, int rowSpan)
    {
        Label *l = new Label(text, column, row, columnSpan, rowSpan);
        l->SetBrushGroup("Header");
        l->SetLayoutGroup("HeaderText");
        return l;
    }
}
