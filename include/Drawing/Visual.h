#pragma once

#include <stdint.h>
#include <any>

#include <Input/Point.h>
#include <Drawing/Properties/ParentProperty.h>
#include <Drawing/Rectangle.h>
#include <Drawing/VisualBase/GridContentBase.h>
#include <Drawing/VisualBase/LayoutManager.h>
#include <Drawing/VisualBase/Renderable.h>
#include <Drawing/VisualBase/ToolTipBase.h>

namespace xit::Drawing
{
    class Window; // Forward declaration

    class Visual : public ToolTipBase,
                   public GridContentBase,
                   public Renderable,
                   public ParentProperty
    {
    private:
        std::any tag;

    protected:
        virtual void OnNameChanged(EventArgs &e) override;
        virtual void NotifyWindowOfInvalidation() override;

    public:
        __always_inline std::any &GetTag() { return tag; }
        __always_inline const std::any &GetTag() const { return tag; }
        __always_inline void SetTag(const std::any &value) { tag = value; }

        Window* GetWindow();

        Visual();
        virtual ~Visual() = default; // Ensure proper cleanup of derived classes

        bool operator==(Visual *other)
        {
            return this == other;
        }
    };
}
