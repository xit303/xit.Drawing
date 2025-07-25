#pragma once

#include <glm.hpp>

#include <Drawing/Visual.h>
#include <Drawing/TextWrapping.h>
#include <Drawing/UIDefaults.h>
#include <Drawing/Properties/FontProperty.h>
#include <Drawing/Properties/TextProperty.h>

#include <OpenGL/Graphics.h>
#include <OpenGL/Scene2D.h>
#include <OpenGL/OpenGLExtensions.h>
#include <OpenGL/Text/TextRenderer.h>
#include <OpenGL/Text/FontStorage.h>

namespace xit::Drawing
{
    class Label : public Visual,
                  public TextProperty,
                  public FontProperty
    {
    private:
        glm::vec4 color;
        int textTop;
        Size textSize;

    public:
        Label(int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1);
        Label(const std::string &text, int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1);

    protected:
        virtual void OnTextChanged() override;
        virtual void OnTextWrappingChanged() override;
        virtual void OnFontSizeChanged() override;

        virtual void OnForegroundChanged(EventArgs &e) override;

        virtual int OnMeasureWidth(int available) override;
        virtual int OnMeasureHeight(int available) override;

        // void OnUpdate(const Rectangle &bounds) override;
        virtual void OnLayoutCompleted(const Rectangle &bounds) override;
        virtual void OnRender() override;

    public:
        virtual void SetDPIScale(float scaleX, float scaleY) override;
        virtual Size Measure(const Size &availableSize) override;
        Size &MeasureText();

        static const void MeasureText(const std::string &fontName, int fontSize, const std::string &text, Size &target);

        //******************************************************************************
        // public static Create Methods
        //******************************************************************************

        static Label *CreateHeader(int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1);
        static Label *CreateHeader(const std::string &text, int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1);
    };
}
