#include "MainWindow.h"
#include <Drawing/FileDialog.h>
#include <Threading/Dispatcher.h>

namespace PassMaga
{
    MainWindow::MainWindow()
    {
        textBox = nullptr;
    }

    MainWindow::~MainWindow()
    {
        if (textBox != nullptr)
        {
            delete textBox;
            textBox = nullptr;
        }
    }

    void MainWindow::OnInitializeComponent()
    {
        textBox = new TextBox();
        textBox->SetName("MainTextBox");
        textBox->SetIsPassword(true);
        textBox->SetHintText("Enter your password here");
        textBox->SetTextAlignment(HorizontalAlignment::Center);
        SetContent(textBox);

        textBox->Focus();
    }
}