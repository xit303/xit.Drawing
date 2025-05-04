#pragma once

#include <Drawing/Properties/OrientationProperty.h>
#include <Drawing/Properties/OrientationDirectionProperty.h>
#include <Drawing/Properties/IsActiveProperty.h>
#include <Drawing/Properties/CanActivateProperty.h>
#include <Drawing/Properties/CanDeactivateProperty.h>
#include <Drawing/Properties/IsErrorProperty.h>
#include <Drawing/Properties/IsHighlightedProperty.h>

#include <Drawing/ContainerBase.h>

namespace xit::Drawing
{
    class Container : public ContainerBase,
                      public OrientationProperty,
                      public OrientationDirectionProperty,
                      public IsHighlightedProperty,
                      public CanActivateProperty,
                      public CanDeactivateProperty,
                      public IsActiveProperty,
                      public IsErrorProperty
    {
    private:
        // private MouseHandler mouseHandler;
        // private Border focusOverlay; // TODO is this a better way ? -> No this does not work -> Padding .... etc.
        // private Border visualStateOverlay; // TODO is this a better way ?

        std::string columnsOrRows;

        bool wasPressed;
        bool useOrientation;

        // BoolSetting *isActiveSetting;

        // void IsActiveSetting_ValueChanged(bool value)
        // {
        //     if (GetIsActive() != value)
        //     {
        //         SetIsActive(value);
        //     }
        // }

        void UpdateOrientation();

    protected:
        virtual void OnIsErrorChanged(EventArgs &e) override;
        virtual void OnIsActiveChanged(EventArgs &e) override;
        virtual void OnOrientationChanged(EventArgs &e) override;
        virtual void OnOrientationDirectionChanged(EventArgs &e) override;

        virtual void UpdateState() override;
        std::string GetState();

        virtual void OnChildAdded(Visual &content, EventArgs &e) override;
        virtual void OnChildRemoved(Visual &content, EventArgs &e) override;

        virtual void OnInputPressed(MouseEventArgs &e) override;
        virtual void OnInputReleased(MouseEventArgs &e) override;

        virtual void OnKeyDown(KeyEventArgs &e) override;
        virtual void OnKeyUp(KeyEventArgs &e) override;

        virtual void OnInvalidated(EventArgs &e) override;

    public:
        __always_inline bool GetUseOrientation() const { return useOrientation; }
        void SetUseOrientation(bool value)
        {
            if (useOrientation != value)
            {
                useOrientation = value;
            }
        }

        Container();

        static void UpdateColumns(Container &container, int startIndex);

        /// <summary>
        /// Updates all childs row indices of the given grid from startIndex to the end.
        /// Mostly used if a child has been removed inbetween.
        /// </summary>
        /// <param name="container">The container which holds the items</param>
        /// <param name="startIndex">The index where the update should start. Passing 0 will update all children.</param>
        static void UpdateRows(Container &container, int startIndex);
    };
}
