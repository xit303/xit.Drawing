#pragma once

#include <string>
#include <Event.h>
#ifdef DEBUG_INITIALIZATION
#include <chrono>
#include <iostream>
#endif

namespace xit
{
    /**
     * @brief Represents a property for a brush group.
     */
    class BrushGroupProperty
    {
    private:
        std::string brushGroup;

        /**
         * @brief Handles the brush group changed event.
         */
        void HandleBrushGroupChanged()
        {
#ifdef DEBUG_INITIALIZATION
            static int callCount = 0;
            callCount++;
            auto start = std::chrono::steady_clock::now();
#endif
            EventArgs e;
            BrushGroupChanged(*this, e);
#ifdef DEBUG_INITIALIZATION
            auto afterEvent = std::chrono::steady_clock::now();
#endif
            OnBrushGroupChanged(e);
#ifdef DEBUG_INITIALIZATION
            auto end = std::chrono::steady_clock::now();
            auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            auto eventDuration = std::chrono::duration_cast<std::chrono::microseconds>(afterEvent - start);
            auto onChangedDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - afterEvent);
            
            if (totalDuration.count() > 100 || callCount <= 5) // Log first 5 calls or any > 100μs
            {
                std::cout << ">>> BRUSH GROUP PROPERTY #" << callCount << ": Total=" 
                          << totalDuration.count() << "μs, Event=" << eventDuration.count() 
                          << "μs, OnChanged=" << onChangedDuration.count() << "μs <<<" << std::endl;
            }
#endif
        }

    protected:
        /**
         * @brief Called when the brush group is changed.
         * 
         * You can override this method in a derived class to handle the change in the brush group.
         * 
         * @param e Event arguments.
         */
        virtual void OnBrushGroupChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the brush group value.
         * @return The brush group value.
         */
        __always_inline const std::string &GetBrushGroup() const { return brushGroup; }

        /**
         * @brief Sets the brush group value.
         * @param value The new brush group value.
         */
        void SetBrushGroup(const std::string &value)
        {
#ifdef DEBUG_INITIALIZATION
            auto start = std::chrono::steady_clock::now();
            std::cout << ">>> DEBUG: SetBrushGroup called with value='" << value << "', current='" << brushGroup << "' <<<" << std::endl;
#endif
            if (brushGroup != value)
            {
#ifdef DEBUG_INITIALIZATION
                std::cout << ">>> DEBUG: Brush group changing from '" << brushGroup << "' to '" << value << "' <<<" << std::endl;
                auto beforeChange = std::chrono::steady_clock::now();
#endif
                brushGroup = value;
#ifdef DEBUG_INITIALIZATION
                auto afterAssignment = std::chrono::steady_clock::now();
                std::cout << ">>> DEBUG: About to call HandleBrushGroupChanged() <<<" << std::endl;
#endif
                HandleBrushGroupChanged();
#ifdef DEBUG_INITIALIZATION
                auto afterHandle = std::chrono::steady_clock::now();
                std::cout << ">>> DEBUG: HandleBrushGroupChanged() completed <<<" << std::endl;
                
                auto assignmentDuration = std::chrono::duration_cast<std::chrono::microseconds>(afterAssignment - beforeChange);
                auto handleDuration = std::chrono::duration_cast<std::chrono::microseconds>(afterHandle - afterAssignment);
                auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(afterHandle - start);
                
                std::cout << ">>> SETBRUSHGROUP TIMING for '" << value << "': Total=" << totalDuration.count() 
                          << "μs, Assignment=" << assignmentDuration.count() 
                          << "μs, Handle=" << handleDuration.count() << "μs <<<" << std::endl;
#endif
            }
#ifdef DEBUG_INITIALIZATION
            else
            {
                auto end = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                if (duration.count() > 100)
                {
                    std::cout << ">>> SETBRUSHGROUP: No change needed, took " << duration.count() << "μs <<<" << std::endl;
                }
            }
#endif
        }

        /**
         * @brief Event triggered when the brush group is changed.
         */
        Event<BrushGroupProperty &, EventArgs &> BrushGroupChanged;

        /**
         * @brief Default constructor.
         */
        BrushGroupProperty() : brushGroup(), BrushGroupChanged() {}

        /**
         * @brief Constructor with brush group value.
         * @param brushGroup The initial brush group value.
         */
        BrushGroupProperty(std::string brushGroup) : brushGroup(brushGroup), BrushGroupChanged() {}

        /**
         * @brief Copy constructor.
         * @param other The other BrushGroupProperty to copy from.
         */
        BrushGroupProperty(const BrushGroupProperty &other) : brushGroup(other.brushGroup), BrushGroupChanged() {}

        /**
         * @brief Destructor.
         */
        virtual ~BrushGroupProperty() {}
    };
}