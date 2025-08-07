#pragma once

#include <Properties/EnabledProperty.h>
#include <Drawing/Brushes/ImageBrush.h>
#include <Drawing/Properties/BackgroundProperty.h>
#include <Drawing/Properties/BorderBrushProperty.h>
#include <Drawing/Properties/BrushGroupProperty.h>
#include <Drawing/Properties/ForegroundProperty.h>
#include <Drawing/Properties/RotationProperty.h>
#include <Drawing/Properties/ZIndexProperty.h>
#include <Drawing/VisualBase/LayoutManager.h>
#include <Drawing/VisualBase/VisualStateManager.h>
#include <OpenGL/Texture.h>
#include <OpenGL/Graphics.h>
#include <OpenGL/Scene2D.h>

namespace xit::Drawing::VisualBase
{
    class Renderable : public LayoutManager,
                       public Properties::EnabledProperty,
                       public BrushGroupProperty,
                       public RotationProperty,
                       public ZIndexProperty,
                       public BackgroundProperty,
                       public ForegroundProperty,
                       public BorderBrushProperty,
                       public VisualStateManager
    {
    private:
        using Texture = xit::OpenGL::Texture;

        float *backgroundColors;
        float *foregroundColors;
        float *borderColors;
        bool clipToBounds;

        bool isBrushGroupChanging;
        BrushVisualStateGroup *brushVisualStateGroup;
        BrushVisualState *currentBrushVisualState;

        bool isLayoutGroupChanging;
        LayoutVisualStateGroup *layoutVisualStateGroup;
        LayoutVisualState *currentLayoutVisualState;

        static Renderable *firstInvalidator;

        void HandleBrushGroupChanged();

    protected:
        const OpenGL::Texture *backgroundTexture;
        const OpenGL::Texture *borderTexture;

        virtual void UpdateState();
        virtual void OnEnabledChanged(EventArgs &e) override;
        virtual void OnThemeChanged(EventArgs &e);
        virtual void OnBackgroundChanged(EventArgs &e) override;
        virtual void OnForegroundChanged(EventArgs &e) override;
        virtual void OnBorderBrushChanged(EventArgs &e) override;

        virtual void OnBrushGroupChanged(EventArgs &e);
        virtual void OnUpdateBrushes(BrushVisualState *value);
        virtual void UpdateBrushVisualState() override;

        virtual void OnLayoutGroupChanged(EventArgs &e) override;
        virtual void OnUpdateLayout(LayoutVisualState *value);
        virtual void UpdateLayoutVisualState() override;
        virtual bool ShouldUpdateLayoutForState(const std::string &state) override;

        virtual void OnVisualStateChanged(EventArgs &e) override;

        virtual void OnRender();

    public:
        Renderable();
        virtual ~Renderable();

        const bool &ClipToBounds = clipToBounds;
        void SetClipToBounds(bool value);

        bool HasVisualState(const std::string &state) const
        {
            // Check if the state exists in either brush or layout visual state groups
            if (brushVisualStateGroup)
            {
                if (brushVisualStateGroup->HasVisualState(state))
                {
                    return true;
                }
            }
            
            // Also check layout visual state group
            if (layoutVisualStateGroup)
            {
                if (layoutVisualStateGroup->HasVisualState(state))
                {
                    return true;
                }
            }
            
            // If no local groups, check theme manager for both types
            if (!brushVisualStateGroup || !layoutVisualStateGroup)
            {
                if (!brushVisualStateGroup)
                {
                    BrushVisualStateGroup *themeGroup = ThemeManager::Default.GetBrushVisualStateGroup(GetBrushGroup());
                    if (themeGroup && themeGroup->HasVisualState(state))
                    {
                        return true;
                    }
                }
                
                if (!layoutVisualStateGroup)
                {
                    LayoutVisualStateGroup *themeLayoutGroup = ThemeManager::Default.GetLayoutVisualStateGroup(GetLayoutGroup());
                    if (themeLayoutGroup && themeLayoutGroup->HasVisualState(state))
                    {
                        return true;
                    }
                }
            }
            
            return false;
        }

        void Render();
    };
} // namespace xit::Drawing::VisualBase
