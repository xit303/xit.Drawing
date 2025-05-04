#pragma once

// #include "../Settings/ExpanderSettings.h"

#include "HeaderedContainer.h"
#include "Buttons/HeaderButton.h"

namespace xit::Drawing
{
    class Expander : public HeaderedContainer//, public IExpandable
    {
    private:
        // ExpanderSettings* expanderSettings;
        HeaderButton expanderHeaderButton;

        // BoolSetting* isExpandedSetting;
        bool isExpanded;
        bool isExpandable;

    public:

        inline bool IsExpanded() { return isExpanded; }
        void SetIsExpanded(bool value)
        {
            if (isExpanded != value)
            {
                if (isExpanded != value)
                {
                    isExpanded = value;
                    expanderHeaderButton.SetIsActive(value);

                    // if (isExpandedSetting != nullptr)
                    // {
                    //     if (isExpandable && isExpandedSetting->Value() != value)
                    //         isExpandedSetting->SetValue(value);
                    // }

                    needLeftRecalculation = true;
                    needTopRecalculation = true;
                    needWidthRecalculation = true;
                    needHeightRecalculation = true;

                    SetContentContainerVisibility(isExpanded ? Visibility::Visible : Visibility::Collapsed);

                    HandleExpandedChanged();

                    Invalidate();
                }
            }
        }
            
        inline bool IsExpandable() { return isExpandable; }
        void SetIsExpandable(bool value)
        {
            if (isExpandable != value)
            {
                isExpandable = value;
                expanderHeaderButton.SetIsExpandable(value);

                if (value)
                {
                    // TODO restore previous state
                    // if (isExpandedSetting != nullptr)
                    // {
                    //     SetIsExpanded(isExpandedSetting->Value());
                    // }
                    SetIsExpanded(false); // TODO remove if above is enabeld
                }
                else
                {
                    // as long as IsExpandable is set to false the isExpandedSetting will not be touched
                    // therefore we can set the value directly
                    SetIsExpanded(false);
                }
            }
        }

        //******************************************************************************
        // #region Text / CTextSource / DefaultText / HeaderContent
        //******************************************************************************
        
        inline void SetText(const std::string& value) { expanderHeaderButton.SetText(value); }
        //inline void SetTextSource(const std::string& value) { expanderHeaderButton.SetTextSource(value); }
        // inline void SetDefaultText(const std::string& value) { expanderHeaderButton.SetDefaultText(value); }
 
        inline Visual* HeaderContent() { return expanderHeaderButton.HeaderContent(); }
        inline void SetHeaderContent(Visual* value) { expanderHeaderButton.SetHeaderContent(value); }

        Event<bool> IsExpandedChanged;

        Expander()
        {
            // isExpandedSetting = nullptr;
            // expanderSettings = nullptr;
            isExpanded = false;
            isExpandable = true;

            SetLayoutGroup("Expander");
            SetBrushGroup("Container");
            
            expanderHeaderButton.SetVerticalAlignment(VerticalAlignment::Stretch);
            expanderHeaderButton.IsActiveChanged.Add(&Expander::ExpanderHeaderButton_ActiveChanged, this);
            SetHeader(&expanderHeaderButton);

            SetContentContainerVisibility(Visibility::Collapsed);

            // InstanceHandler<ExpanderSettings>::RequestInstance(&Expander::InstanceRequestComplete, this);
        }

    private:
        // void InstanceRequestComplete(ExpanderSettings* requestedInstance)
        // {
        //     /*if (expanderSettings)
        //         expanderSettings->PropertyChanged -= ExpanderSettings_ValueChanged;*/

        //     expanderSettings = requestedInstance;

        //     /*if (expanderSettings)
        //         expanderSettings->PropertyChanged += ExpanderSettings_ValueChanged;*/

        //     CheckExpanderSettings();
        // }

        void CheckExpanderSettings()
        {
            // if (expanderSettings != nullptr && !GetName().empty())
            // {
            //     BoolSetting* setting = (BoolSetting*)expanderSettings->TryGetValue(Name);
            //     if (!setting)
            //     {
            //         setting = new BoolSetting(Name, false);
            //         expanderSettings->Add(setting);
            //     }

            //     isExpandedSetting = setting;
                
            //     EventArgs e;
            //     ExpanderSettings_ValueChanged(e);

            //     OnExpanderSettingsSet(expanderSettings);
            // }
        }

        // void ExpanderSettings_ValueChanged(EventArgs& e)
        // {
        //     // set value if enabled
        //     if (expanderSettings->StoreExpanderStates())
        //     {
        //         SetIsExpanded(isExpandedSetting->Value());
        //     }
        // }

        void ExpanderHeaderButton_ActiveChanged(IsActiveProperty& sender, EventArgs& e)
        {
            SetIsExpanded(isExpandable && expanderHeaderButton.GetIsActive());
        }

        void HandleExpandedChanged()
        {
            EventArgs e;
            OnIsExpandedChanged(e);
            IsExpandedChanged(isExpanded);
        }

    protected:
        void OnNameChanged(EventArgs& e) override
        {
            HeaderedContainer::OnNameChanged(e);

            std::string name = GetName() + "Header";
            expanderHeaderButton.SetName(name);
            //expanderHeaderButton.SetTextSource(name);

            CheckExpanderSettings();
        }

        virtual void OnIsExpandedChanged(EventArgs& e) { }
        // virtual void OnExpanderSettingsSet(ExpanderSettings* expanderSettings) { }
    };
}
