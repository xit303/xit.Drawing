#include <Drawing/MainWindowBase.h>
#include <Drawing/TextBox.h>

using namespace xit;
using namespace xit::Drawing;

namespace PassMaga
{
    class MainWindow : public MainWindowBase
    {
    private:
        TextBox *textBox;

        void OnMenuClosed(EventArgs &e)
        {
        }

    public:
        MainWindow();
        virtual ~MainWindow();
        virtual void OnInitializeComponent() override;
    };
}