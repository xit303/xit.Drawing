#pragma once

#include <Drawing/MainMenu.h>

namespace xit::Drawing::Pages
{
    class MainPageBase : public MainMenu
    {
    protected:
        virtual void OnAccountChanged() = 0;

    public:
        MainPageBase();
        virtual void SaveState();

        void LoadAccountData();
    };
}
