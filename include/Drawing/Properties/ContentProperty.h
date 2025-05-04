#pragma once

#include <Drawing/Visual.h>

namespace xit::Drawing::Properties
{
    /**
     * @brief Represents a property that defines the content.
     */
    class ContentProperty
    {
    private:
        Visual *content;

        /**
         * @brief Handles the event when the content changes.
         * @param oldContent The previous content.
         */
        void HandleContentChanged(const Visual *oldContent)
        {
            EventArgs e;
            ContentChanged(*this, e);
            OnContentChanged(e, oldContent, content);
        }

    protected:
        /**
         * @brief Called when the content changes.
         * 
         * You can override this method to add custom logic when the content changes.
         * 
         * @param e The event arguments.
         * @param oldContent The previous content.
         * @param newContent The new content.
         */
        virtual void OnContentChanged(EventArgs &e, const Visual *oldContent, const Visual *newContent) {}

    public:
        /**
         * @brief Gets the content.
         * @return The content.
         */
        __always_inline const Visual &GetContent() const { return *content; }

        /**
         * @brief Sets the content.
         * @param value The new content value.
         */
        void SetContent(Visual *value)
        {
            if (content != value)
            {
                if (content != nullptr)
                {
                    content->SetParent(nullptr);
                }

                Visual *oldContent = content;
                content = value;
                HandleContentChanged(oldContent);

                // if (content != nullptr)
                // {
                //     content->SetDPIScale(GetScaleX(), GetScaleY());
                //     content->SetParent(this);
                // }
            }
        }

        /**
         * @brief Event triggered when the content changes.
         */
        Event<ContentProperty &, EventArgs &> ContentChanged;

        /**
         * @brief Default constructor.
         */
        ContentProperty() : content(nullptr) {}

        /**
         * @brief Constructor with content parameter.
         * @param content The initial content value.
         */
        ContentProperty(Visual *content) : content(content) {}

        /**
         * @brief Copy constructor.
         * @param other The other ContentProperty to copy from.
         */
        ContentProperty(const ContentProperty &other) : content(other.content) {}

        /**
         * @brief Destructor.
         */
        virtual ~ContentProperty() {}
    };
}