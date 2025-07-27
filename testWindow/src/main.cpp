#include <Application/App.h>
#include "MainWindow.h"

using namespace xit;
using namespace PassMaga;

int main(int argc, char **argv)
{
    std::string appFile = argv[0];
    std::string appName = "testWindow";
    std::string version = "0.1.0";

    App::Initialize(appName, version, appFile);
    ThemeManager::InitializeDefault();

    WindowSettings windowSettings;
    windowSettings.Load(App::UserPath());

    MainWindow window;

    if (window.Initialize(windowSettings, appName + " v" + version))
    {
        try
        {
            window.Show();
        }
        catch (const std::exception &e)
        {
            Logger::Log("main", e);
            std::cerr << e.what() << '\n';
        }
    }

    App::Close();

    return 0;
}
