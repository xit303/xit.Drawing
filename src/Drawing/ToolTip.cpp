#include <Drawing/ToolTip.h>

namespace xit::Drawing
{
    Timer ToolTip::startTimer;
    Timer ToolTip::stopTimer;

    ToolTip &ToolTip::GetInstance()
    {
        static ToolTip instance;
        return instance;
    }

    ToolTip::ToolTip()
    {
        SetBrushGroup("ToolTip");
        SetLayoutGroup("ToolTip");

        SetName("ToolTip");

        SetColumns("Auto");
        SetRows("Auto");

        SetIsAbsolutePosition(true);
        SetVisibility(Visibility::Collapsed);

		textLabel.SetHorizontalAlignment(HorizontalAlignment::Left);
		SetVerticalContentAlignment(VerticalAlignment::Center);

        startTimer.Elapsed.Add([&]( EventArgs &e) {
            GetInstance().SetVisibility(Visibility::Collapsed);
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
        GetInstance().SetDPIScale(scaleX, scaleY);
    }

    void ToolTip::DoUpdate(Rectangle &bounds)
    {
        GetInstance().UpdateLayout(bounds);
    }
    void ToolTip::DoRender()
    {
        GetInstance().Render();
    }

    void ToolTip::Show(const std::string &text, int x, int y, int duration)
    {
        if (text.empty())
            return;

        ToolTip &instance = GetInstance();

        if (!instance.GetIsVisible())
        {
            instance.SetVisibility(Visibility::Visible);

            instance.textLabel.SetText(text);
            instance.SetPosition(x, y);
            instance.Invalidate();
        }

        if (duration > 0)
        {
            startTimer.SetInterval(duration);
            startTimer.Start();
        }
    }

    void ToolTip::Hide()
    {
        GetInstance().SetVisibility(Visibility::Collapsed);
    }
}
