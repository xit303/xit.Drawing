#pragma once

#include <Event.h>
#include <Input/ILocation.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the location.
     */
    class Location : public ILocation
    {
    private:
        int x;
        int y;
        int offsetX;
        int offsetY;
        bool isAbsolutePosition;

        /**
         * @brief Sets the left position privately.
         * @param value The new left position value.
         * @return True if the value was changed, false otherwise.
         */
        bool SetLeftPrivate(int value)
        {
            if (x != value)
            {
                x = value;
                HandleLeftChanged();
                return true;
            }
            return false;
        }

        /**
         * @brief Sets the top position privately.
         * @param value The new top position value.
         * @return True if the value was changed, false otherwise.
         */
        bool SetTopPrivate(int value)
        {
            if (y != value)
            {
                y = value;
                HandleTopChanged();
                return true;
            }
            return false;
        }

        /**
         * @brief Handles the event when the left position changes.
         */
        void HandleLeftChanged()
        {
            EventArgs e;
            LeftChanged(*this, e);
            OnLeftChanged(e);
        }

        /**
         * @brief Handles the event when the top position changes.
         */
        void HandleTopChanged()
        {
            EventArgs e;
            TopChanged(*this, e);
            OnTopChanged(e);
        }

        /**
         * @brief Handles the event when the location changes.
         */
        void HandleLocationChanged()
        {
            EventArgs e;
            LocationChanged(*this, e);
            OnLocationChanged(e);
        }

    public:
        /**
         * @brief Gets the x-coordinate.
         * @return The x-coordinate.
         */
        virtual __always_inline int GetX() const override { return x - offsetX; }

        /**
         * @brief Sets the x-coordinate.
         * @param value The new x-coordinate value.
         */
        virtual void SetX(int value) override
        {
            if (SetLeftPrivate(value))
                HandleLocationChanged();
        }

        /**
         * @brief Gets the left position.
         * @return The left position.
         */
        virtual __always_inline int GetLeft() const override { return x - offsetX; }

        /**
         * @brief Sets the left position.
         * @param value The new left position value.
         */
        virtual void SetLeft(int value) override
        {
            if (SetLeftPrivate(value))
                HandleLocationChanged();
        }

        /**
         * @brief Gets the y-coordinate.
         * @return The y-coordinate.
         */
        virtual __always_inline int GetY() const override { return y - offsetY; }

        /**
         * @brief Sets the y-coordinate.
         * @param value The new y-coordinate value.
         */
        virtual void SetY(int value) override
        {
            if (SetTopPrivate(value))
                HandleLocationChanged();
        }

        /**
         * @brief Gets the top position.
         * @return The top position.
         */
        virtual __always_inline int GetTop() const override { return y - offsetY; }

        /**
         * @brief Sets the top position.
         * @param value The new top position value.
         */
        virtual void SetTop(int value) override
        {
            if (SetTopPrivate(value))
                HandleLocationChanged();
        }

        /**
         * @brief Gets the absolute position.
         * @return True if the position is absolute, false otherwise.
         */
        virtual __always_inline bool GetIsAbsolutePosition() const override { return isAbsolutePosition; }

        /**
         * @brief Sets the absolute position.
         * @param value The new absolute position value.
         */
        virtual void SetIsAbsolutePosition(bool value) override
        {
            isAbsolutePosition = value;
            if (!isAbsolutePosition)
            {
                offsetX = 0;
                offsetY = 0;
            }
        }

        virtual void SetAbsoluteOffset(int x, int y) override
        {
            offsetX = x;
            offsetY = y;
        }

        Event<Location &, EventArgs &> LeftChanged;
        Event<Location &, EventArgs &> TopChanged;
        Event<Location &, EventArgs &> LocationChanged;

        /**
         * @brief Default constructor.
         */
        Location() : x(0), y(0), offsetX(0), offsetY(0), isAbsolutePosition(false) {}

        /**
         * @brief Parameterized constructor.
         * @param x The x-coordinate.
         * @param y The y-coordinate.
         */
        Location(int x, int y) : x(x), y(y), offsetX(0), offsetY(0), isAbsolutePosition(false) {}

        /**
         * @brief Sets the position.
         * @param x The new x-coordinate.
         * @param y The new y-coordinate.
         */
        void SetPosition(int x, int y)
        {
            bool set = SetLeftPrivate(x);
            set |= SetTopPrivate(y);

            if (set)
                HandleLocationChanged();
        }

        /**
         * @brief Sets the position.
         * @param location The new location.
         */
        void SetPosition(const Location &location)
        {
            bool set = SetLeftPrivate(location.GetLeft());
            set |= SetTopPrivate(location.GetTop());

            if (set)
                HandleLocationChanged();
        }

    protected:
        /**
         * @brief Called when the left position changes.
         * @param e The event arguments.
         */
        virtual void OnLeftChanged(EventArgs &e) {}

        /**
         * @brief Called when the top position changes.
         * @param e The event arguments.
         */
        virtual void OnTopChanged(EventArgs &e) {}

        /**
         * @brief Called when the location changes.
         * @param e The event arguments.
         */
        virtual void OnLocationChanged(EventArgs &e) {}
    };
}
