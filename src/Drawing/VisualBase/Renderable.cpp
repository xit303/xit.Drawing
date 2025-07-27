#include <Drawing/VisualBase/Renderable.h>

namespace xit::Drawing::VisualBase
{
    Renderable *Renderable::firstInvalidator = nullptr;

    Renderable::Renderable()
    {
        backgroundColors = nullptr;
        foregroundColors = nullptr;
        borderColors = nullptr;
        clipToBounds = false;
        isBrushGroupChanging = false;
        brushVisualStateGroup = nullptr;
        currentBrushVisualState = nullptr;
        layoutVisualStateGroup = nullptr;
        currentLayoutVisualState = nullptr;
        isLayoutGroupChanging = false;
        backgroundTexture = nullptr;
        borderTexture = nullptr;

        ThemeManager::ThemeChanged.Add(&Renderable::OnThemeChanged, this);
    }

    Renderable::~Renderable()
    {
        if (backgroundColors)
            delete backgroundColors;
        if (foregroundColors)
            delete foregroundColors;
        if (borderColors)
            delete borderColors;
    }

    void Renderable::SetClipToBounds(bool value)
    {
        if (clipToBounds != value)
        {
            clipToBounds = value;
        }
    }

    void Renderable::Render()
    {
        int actualWidth = GetActualWidth();
        int actualHeight = GetActualHeight();

        if (GetIsVisible() && actualWidth > 0 && actualHeight > 0)
        {
            int cachedRect[4] = {0};
            GLboolean enabled = glIsEnabled(GL_SCISSOR_TEST);

            if (clipToBounds) // this should set a Geometry.ClipToBounds value
            {
                if (enabled == 1)
                {
                    glGetIntegerv(GL_SCISSOR_BOX, cachedRect);
                }

                // TODO something here is really wrong
                // Left and top seem to be calculated wrong because some items are cut off

                // convert bounds to screen coordinates
                Rectangle bounds = this->bounds;
                bounds.SetTop(Scene2D::CurrentScene().GetHeight() - bounds.GetTop() - bounds.GetHeight());

                int top = std::max(renderTop, bounds.GetTop());
                int left = std::max(renderLeft, bounds.GetLeft());
                int width = left + actualWidth > bounds.GetRight() ? bounds.GetRight() - left : actualWidth;
                int height = top + actualHeight > bounds.GetBottom() ? bounds.GetBottom() - top : actualHeight;

                if (enabled)
                {
                    left = std::max(left, cachedRect[0]);
                    top = std::max(top, cachedRect[1]);

                    int lastXMax = cachedRect[0] + cachedRect[2];
                    int myXMax = renderLeft + actualWidth;

                    width = std::min(lastXMax, myXMax) - left;

                    int lastYMax = cachedRect[1] + cachedRect[3];
                    int myYMax = renderTop + actualHeight;

                    height = std::min(lastYMax, myYMax) - top;
                }

                if (width > 0 && height > 0)
                {
                    glScissor(left, top, width, height);
                    glEnable(GL_SCISSOR_TEST);
                }
            }

            OnRender();

            if (clipToBounds || this == firstInvalidator)
            {
                if (enabled == 0 || this == firstInvalidator)
                {
                    glDisable(GL_SCISSOR_TEST);
                }
                else if (enabled)
                {
                    glScissor(cachedRect[0], cachedRect[1], cachedRect[2], cachedRect[3]);
                }
            }
        }
    }

    void Renderable::UpdateState()
    {
        SetVisualState(GetEnabled() ? "Normal" : "Disabled");
    }

    void Renderable::OnEnabledChanged(EventArgs &e)
    {
        UpdateState();
    }

    void Renderable::OnThemeChanged(EventArgs &e)
    {
        HandleBrushGroupChanged();
        UpdateLayoutVisualState(); // TODO why did i make this UpdateLayoutVisualState instead of HandleLayoutGroupChanged() ???
    }

    void Renderable::OnBackgroundChanged(EventArgs &e)
    {
        const ImageBrush *imageBrush = dynamic_cast<const ImageBrush *>(GetBackground());
        if (imageBrush)
        {
            backgroundTexture = Texture::FindOrCreateTexture(imageBrush->GetFileName(), imageBrush->GetWidth(), imageBrush->GetHeight());
        }
        else
        {
            backgroundColors = Graphics::GetBrushColor(GetBackground());
            if (backgroundTexture)
                backgroundTexture = nullptr;
        }
        Invalidate();
    }

    void Renderable::OnForegroundChanged(EventArgs &e)
    {
        if (foregroundColors)
        {
            delete foregroundColors;
            foregroundColors = nullptr;
        }
        if (GetInheritForeground() && GetForeground())
        {
            foregroundColors = Graphics::GetBrushColor(GetForeground());
        }
        Invalidate();
    }

    void Renderable::OnBorderBrushChanged(EventArgs &e)
    {
        if (borderColors)
        {
            delete borderColors;
            borderColors = nullptr;
        }
        const ImageBrush *imageBrush = dynamic_cast<const ImageBrush *>(GetBorderBrush());
        if (imageBrush)
        {
            borderTexture = Texture::FindOrCreateTexture(imageBrush->GetFileName(), imageBrush->GetWidth(), imageBrush->GetHeight());
        }
        else
        {
            borderColors = Graphics::GetBrushColor(GetBorderBrush());
            borderTexture = nullptr;
        }

        Invalidate();
    }

    void Renderable::OnBrushGroupChanged(EventArgs &e)
    {
        isBrushGroupChanging = true;
        UpdateBrushVisualState();
    }

    void Renderable::OnUpdateBrushes(BrushVisualState *value)
    {
        if (value != nullptr)
        {
            SetBackground(value->GetBackground());
            SetForeground(value->GetForeground());
            SetBorderBrush(value->GetBorderBrush());
        }
    }

    void Renderable::UpdateBrushVisualState()
    {
        BrushVisualState *value = nullptr;
        if (brushVisualStateGroup != nullptr && !isBrushGroupChanging)
        {
            if ((value = brushVisualStateGroup->GetVisualState(visualState)))
            {
                OnUpdateBrushes(value);
                currentBrushVisualState = value;
            }
            else if (currentBrushVisualState)
            {
                visualState = currentBrushVisualState->GetName();
            }
        }
        else
        {
            BrushVisualStateGroup *visualStateGroup = ThemeManager::Default.GetBrushVisualStateGroup(GetBrushGroup());
            if (visualStateGroup)
            {
                if ((value = visualStateGroup->GetVisualState(visualState)))
                {
                    OnUpdateBrushes(value);
                    currentBrushVisualState = value;
                    return;
                }
                else if (currentBrushVisualState)
                {
                    visualState = currentBrushVisualState->GetName();
                    return;
                }
            }
            OnUpdateBrushes(nullptr);
            return;
        }
    }

    void Renderable::OnLayoutGroupChanged(EventArgs &e)
    {
        isLayoutGroupChanging = true;
        UpdateLayoutVisualState();
        Invalidate();
    }

    void Renderable::OnUpdateLayout(LayoutVisualState *value)
    {
        if (value)
        {
            SetWidth(value->GetWidth());
            SetMinWidth(value->GetMinWidth());
            SetMaxWidth(value->GetMaxWidth());

            SetHeight(value->GetHeight());
            SetMinHeight(value->GetMinHeight());
            SetMaxHeight(value->GetMaxHeight());

            SetMargin(value->GetMargin());
            SetPadding(value->GetPadding());
            SetBorderThickness(value->GetBorderThickness());

            // TODO is this correct? In LayoutManager we do this in OnScaleChanged
            // maybe we have to do it because if we use SetDPIScale from ScaleProperty
            // we don't call OnScaleChanged if scaleX and scaleY did not change
            float scaleX = GetScaleX();
            float scaleY = GetScaleY();
            SetMarginScale(scaleX, scaleY);
            SetPaddingScale(scaleX, scaleY);
            SetBorderThicknessScale(scaleX, scaleY);
            Sizeable::Scale(scaleX, scaleY);

            SetCornerRadius(value->GetCornerRadius());

            SetHorizontalAlignment(value->GetHorizontalAlignment());
            SetVerticalAlignment(value->GetVerticalAlignment());
        }
    }

    void Renderable::UpdateLayoutVisualState()
    {
        LayoutVisualState *value = nullptr;
        if (layoutVisualStateGroup != nullptr && !isLayoutGroupChanging)
        {
            if ((value = layoutVisualStateGroup->GetVisualState(visualState)))
            {
                OnUpdateLayout(value);
                currentLayoutVisualState = value;
            }
            else if (currentLayoutVisualState)
            {
                visualState = currentLayoutVisualState->GetName();
            }
        }
        else
        {
            isLayoutGroupChanging = false;
            LayoutVisualStateGroup *visualStateGroup = ThemeManager::Default.GetLayoutVisualStateGroup(GetLayoutGroup());
            if (visualStateGroup)
            {
                if ((value = visualStateGroup->GetVisualState(visualState)))
                {
                    layoutVisualStateGroup = visualStateGroup;
                    OnUpdateLayout(value);
                    currentLayoutVisualState = value;
                    return;
                }
                else if (currentLayoutVisualState)
                {
                    visualState = currentLayoutVisualState->GetName();
                    return;
                }
            }
            OnUpdateLayout(nullptr);
        }
    }

    void Renderable::OnVisualStateChanged(EventArgs &e)
    {
        Invalidate();
    }

    void Renderable::OnRender()
    {
        Graphics::DrawRectangle(GetLeft(), renderLeft, GetTop(), renderTop, GetZIndex(), actualWidth, actualHeight, GetRotation(), backgroundColors, foregroundColors, borderColors, backgroundTexture, borderTexture, GetBorderThickness(), GetCornerRadius());
    }

    void Renderable::HandleBrushGroupChanged()
    {
        if (isBrushGroupChanging)
        {
            return;
        }

        isBrushGroupChanging = true;

        if (brushVisualStateGroup != nullptr)
        {
            // TODO brushVisualStateGroup->PropertyChanged -= BrushVisualStateGroup_PropertyChanged;
            brushVisualStateGroup = nullptr;
        }

        BrushVisualStateGroup *value = ThemeManager::Active().GetBrushVisualStateGroup(GetBrushGroup());
        if (value)
        {
            brushVisualStateGroup = value;
            // TODO brushVisualStateGroup->PropertyChanged += BrushVisualStateGroup_PropertyChanged;
        }

        UpdateBrushVisualState();

        isBrushGroupChanging = false;

        EventArgs e;
        BrushGroupChanged(*this, e);
        OnBrushGroupChanged(e);
    }
}