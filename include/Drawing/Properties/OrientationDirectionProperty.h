#pragma once

#include <Event.h>
// #include <Settings.h>
#include <Drawing/Properties/OrientationDirection.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the orientation direction.
     */
    class OrientationDirectionProperty
    {
    private:
        OrientationDirection orientationDirection;
        // OrientationDirectionSetting *orientationDirectionSetting;

        /**
         * @brief Handles the event when the orientation direction changes.
         */
        void HandleOrientationDirectionChanged()
        {
            // if (orientationDirectionSetting)
            // {
            //     orientationDirectionSetting->SetValue(orientationDirection);
            // }

            EventArgs e;
            OrientationDirectionChanged(*this, e);
            OnOrientationDirectionChanged(e);
        }

        /**
         * @brief Handles the event when the orientation direction setting value changes.
         * @param newValue The new orientation direction value.
         */
        void OrientationDirectionSetting_ValueChanged(const OrientationDirection &newValue)
        {
            SetOrientationDirection(newValue);
        }

    protected:
        /**
         * @brief Called when the orientation direction changes.
         * 
         * You can override this method to add custom logic when the orientation direction changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnOrientationDirectionChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the orientation direction.
         * @return The orientation direction.
         */
        __always_inline OrientationDirection GetOrientationDirection() const { return orientationDirection; }

        /**
         * @brief Sets the orientation direction.
         * @param value The new orientation direction value.
         */
        void SetOrientationDirection(const OrientationDirection &value)
        {
            if (orientationDirection != value)
            {
                orientationDirection = value;
                HandleOrientationDirectionChanged();
            }
        }

        // __always_inline OrientationDirectionSetting* OrientationDirectionSetting() const { return orientationDirectionSetting; }
        // void SetOrientationDirectionSetting(OrientationDirectionSetting *value)
        // {
        //     if (orientationDirectionSetting != value)
        //     {
        //         if (orientationDirectionSetting)
        //         {
        //             orientationDirectionSetting->ValueChanged.Remove(&OrientationProperty::OrientationDirectionSetting_ValueChanged, this);
        //         }

        //         orientationDirectionSetting = value;

        //         if (value)
        //         {
        //             SetOrientationDirection(value->Value());
        //             value->ValueChanged.Add(&OrientationProperty::OrientationDirectionSetting_ValueChanged, this);
        //         }
        //     }
        // }

        /**
         * @brief Event triggered when the orientation direction changes.
         */
        Event<OrientationDirectionProperty &, EventArgs &> OrientationDirectionChanged;

        /**
         * @brief Default constructor.
         */
        OrientationDirectionProperty()
            : orientationDirection(OrientationDirection::Normal)
        // orientationDirectionSetting(nullptr)
        {
        }
    };
}

using namespace xit::Drawing;
