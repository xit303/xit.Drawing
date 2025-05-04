#include <Drawing/Pages/MainPageBase.h>

namespace xit::Drawing::Pages
{
    MainPageBase::MainPageBase() {}
    void MainPageBase::SaveState() {}

    void MainPageBase::LoadAccountData()
    {
        OnAccountChanged();
    }
}
