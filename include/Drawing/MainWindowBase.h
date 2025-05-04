#pragma once

#include <Drawing/Window.h>
#include <Timers/Timer.h>
#include <list>

namespace xit::Drawing
{
    class MainWindowBase : public Window
    {
    private:
        Timer *backgroundInitializationTimer;
        Timer *initializationTimer;

        void DoInitializationActions(EventArgs &e);
        void DoBackgroundInitializationActions(EventArgs &e);

    protected:
        virtual bool OnClosing(bool canceled) override;
        virtual void OnUpdate(const Rectangle &bounds) override;

    public:
        static std::list<Window *> &SubWindows();
        static void AddSubWindow(Window *window) { SubWindows().push_back(window); }
        static void RemoveSubWindow(Window *window) { SubWindows().remove(window); }

        MainWindowBase();

        void SaveState() override;
        virtual void LoadAccountData();
    };
}
