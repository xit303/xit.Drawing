#pragma once

#include <Event.h>
// #include <Settings.h>
#include <Drawing/Properties/Orientation.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the orientation.
     */
    class OrientationProperty
    {
    private:
        Orientation orientation;
        // OrientationSetting *orientationSetting;

        /**
         * @brief Handles the event when the orientation changes.
         */
        void HandleOrientationChanged()
        {
            // if (orientationSetting)
            // {
            //     orientationSetting->SetValue(orientation);
            // }
            EventArgs e;
            OrientationChanged(*this, e);
            OnOrientationChanged(e);
        }

        /**
         * @brief Handles the event when the orientation setting value changes.
         * @param newValue The new orientation value.
         */
        void OrientationSetting_ValueChanged(const Orientation &newValue)
        {
            SetOrientation(newValue);
        }

    protected:
        /**
         * @brief Called when the orientation changes.
         * 
         * You can override this method to add custom logic when the orientation changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnOrientationChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the orientation.
         * @return The orientation.
         */
        __always_inline Orientation GetOrientation() const { return orientation; }

        /**
         * @brief Sets the orientation.
         * @param value The new orientation value.
         */
        void SetOrientation(const Orientation &value)
        {
            if (orientation != value)
            {
                orientation = value;
                HandleOrientationChanged();
            }
        }

        //__always_inline OrientationSetting* OrientationSetting() const { return orientationSetting; }
        // void SetOrientationSetting(OrientationSetting *value)
        // {
        //     if (orientationSetting != value)
        //     {
        //         if (orientationSetting)
        //         {
        //             orientationSetting->ValueChanged.Remove(&OrientationProperty::OrientationSetting_ValueChanged, this);
        //         }

        //         orientationSetting = value;

        //         if (value)
        //         {
        //             SetOrientation(value->Value());
        //             value->ValueChanged.Add(&OrientationProperty::OrientationSetting_ValueChanged, this);
        //         }
        //     }
        // }

        /**
         * @brief Event triggered when the orientation changes.
         */
        Event<OrientationProperty &, EventArgs &> OrientationChanged;

        /**
         * @brief Default constructor.
         */
        OrientationProperty()
            : orientation(Orientation::Horizontal)
        // orientationSetting(nullptr)
        {
        }
    };
}

using namespace xit::Drawing;
