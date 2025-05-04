#pragma once

#include <Event.h>

namespace xit::Drawing::VisualBase
{
    class ToolTipBase
    {
    private:
        std::string toolTip;
        void HandleToolTipChanged()
        {
            EventArgs e;
            ToolTipChanged(*this, e);
            OnToolTipChanged(e);
        }

    protected:
        virtual void OnToolTipChanged(EventArgs &e)
        {
        }

    public:
        const std::string &GetToolTip() const { return toolTip; }
        void SetToolTip(const std::string &value) { toolTip = value; }

   
        Event<ToolTipBase &, EventArgs &> ToolTipChanged;

        ToolTipBase() {}
    };
}
using namespace xit::Drawing::VisualBase;
