#include "Drawing/Label.h"

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
        TextProperty::SetNeedMeasureText(true);
        FontProperty::SetNeedMeasureFont(true);
        Invalidate();
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

    void Label::OnUpdate(const Rectangle &bounds)
    {
        Visual::OnUpdate(bounds);

        if (needLeftRecalculation || needTopRecalculation)
        {
            textTop = Scene2D::CurrentScene().GetHeight() - GetTop() - textSize.GetHeight();
        }
    }

    void Label::OnRender()
    {
        std::string text = GetText();

        if (!text.empty())
        {
            TextRenderer::RenderText(GetFontName(), GetFontSize(), text, GetLeft(), textTop, GetZIndex(), color);
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
                std::cout << "Label::MeasureText: textSize is empty" << std::endl;
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
