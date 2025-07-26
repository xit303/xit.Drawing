#include <Drawing/MainWindowBase.h>

namespace xit::Drawing
{
    std::list<Window *> &MainWindowBase::SubWindows()
    {
        static std::list<Window *> subwindows;
        return subwindows;
    }

    MainWindowBase::MainWindowBase()
    {
        // DefaultTitle = App::Name;
        // UseWindowSettings = true;
        SetName("MainWindowBase");
        SetLayoutGroup("MainWindow");

        // App.AddInitializationAction(AppInitializationPriority.High, () => OnInitializeComponents());

        initializationTimer = new Timer();
        initializationTimer->SetInterval(10);
        initializationTimer->Elapsed.Add(&MainWindowBase::DoInitializationActions, this);
        initializationTimer->Start();

        backgroundInitializationTimer = new Timer();
        backgroundInitializationTimer->SetInterval(100);
        backgroundInitializationTimer->Elapsed.Add(&MainWindowBase::DoBackgroundInitializationActions, this);
        backgroundInitializationTimer->Start();
    }

    void MainWindowBase::DoInitializationActions(EventArgs &e)
    {
        initializationTimer->Stop();

        if (App::DoForegroundInitializationActions())
        {
            initializationTimer->Start();
        }
    }

    void MainWindowBase::DoBackgroundInitializationActions(EventArgs &e)
    {
        backgroundInitializationTimer->Stop();

        if (App::DoBackgroundInitializationActions())
        {
            backgroundInitializationTimer->Start();
        }
    }

    bool MainWindowBase::OnClosing(bool canceled)
    {
        SetIsClosing(true);

        for (Window *window : SubWindows())
        {
            window->Close();
        }
        bool canceledb = Window::OnClosing(canceled);

        return canceled || canceledb;
    }

    void MainWindowBase::OnUpdate(const Rectangle &bounds)
    {
        if (initializationTimer && !initializationTimer->Enabled && App::IsForegroundInitialized)
        {
            delete initializationTimer;
            initializationTimer = nullptr;
        }

        if (backgroundInitializationTimer && !backgroundInitializationTimer->Enabled && App::IsBackgroundInitialized)
        {
            delete backgroundInitializationTimer;
            backgroundInitializationTimer = nullptr;
        }

        Window::OnUpdate(bounds);
    }

    void MainWindowBase::SaveState()
    {
        Window::SaveState();

        App::Save();

        ThemeManager::Save();
        // TemplateManager::Save();
    }

    void MainWindowBase::LoadAccountData()
    {
    }
}
