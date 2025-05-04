#include <Drawing/ToolTip.h>

namespace xit::Drawing
{
    ToolTip *ToolTip::instance = nullptr;
    Timer ToolTip::startTimer;
    Timer ToolTip::stopTimer;

    ToolTip::ToolTip()
    {
        SetBrushGroup("ToolTip");
        SetLayoutGroup("ToolTip");

        SetColumns("Auto");
        SetRows("Auto");

        SetIsAbsolutePosition(true);
        SetVisibility(Visibility::Collapsed);

		textLabel.SetHorizontalAlignment(HorizontalAlignment::Left);
		SetVerticalContentAlignment(VerticalAlignment::Center);

        startTimer.Elapsed.Add([&]( EventArgs &e) {
            instance->SetVisibility(Visibility::Collapsed);
            startTimer.Stop();
        });

        AddChild(&textLabel);
    }

    int ToolTip::OnMeasureWidth(int available)
    {
        return textLabel.MeasureWidth(available);
    }

    int ToolTip::OnMeasureHeight(int available)
    {
        return textLabel.MeasureHeight(available);
    }

    void ToolTip::OnUpdate(const Rectangle &bounds)
    {
        Container::OnUpdate(bounds);

        bool needNewUpdate = false;

        if (GetX() + GetActualWidth() > bounds.GetRight())
        {
            SetX(bounds.GetRight() - GetActualWidth());
            needNewUpdate = true;
        }
        if (GetY() + GetActualHeight() > bounds.GetBottom())
        {
            SetY(bounds.GetBottom() - GetActualHeight());
            needNewUpdate = true;
        }

        if (needNewUpdate)
            Container::OnUpdate(bounds);
    }

    //******************************************************************************
    // Public Static
    //******************************************************************************

    void ToolTip::SetDPI(float scaleX, float scaleY)
    {
        if (!instance)
            instance = new ToolTip();

        instance->SetDPIScale(scaleX, scaleY);
    }

    void ToolTip::DoUpdate(Rectangle &bounds)
    {
        if (!instance)
            instance = new ToolTip();

        instance->Update(bounds);
    }
    void ToolTip::DoRender()
    {
        if (instance)
            instance->Render();
    }

    void ToolTip::Show(const std::string &text, int x, int y, int duration)
    {
        if (text.empty())
            return;

        if (!instance)
            instance = new ToolTip();

        if (!instance->GetIsVisible())
        {
            instance->SetVisibility(Visibility::Visible);

            instance->SetPosition(x, y);
            instance->textLabel.SetText(text);
            instance->Invalidate();
        }

        if (duration > 0)
        {
            startTimer.SetInterval(duration);
            startTimer.Start();
        }
    }

    void ToolTip::Hide()
    {
        if (instance)
            instance->SetVisibility(Visibility::Collapsed);
    }
}
