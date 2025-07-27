#include "MainWindow.h"
#include <Drawing/FileDialog.h>
#include <Threading/Dispatcher.h>

namespace PassMaga
{
    MainWindow::MainWindow()
    {
        textBox1 = nullptr;
        label1 = nullptr;
        container = nullptr;
    }

    MainWindow::~MainWindow()
    {
        if (container != nullptr)
        {
            delete container;
            container = nullptr;
        }
        if (textBox1 != nullptr)
        {
            delete textBox1;
            textBox1 = nullptr;
        }
        if (label1 != nullptr)
        {
            delete label1;
            label1 = nullptr;
        }
    }

    void MainWindow::OnInitializeComponent()
    {
        container = new Container();
        container->SetName("MainContainer");
        container->SetRows("Auto,*,50");
        container->SetRowSpacing(10);

        textBox1 = new TextBox();
        textBox1->SetName("MainTextBox1");
        textBox1->SetIsPassword(true);
        textBox1->SetHintText("Enter your password here");
        textBox1->SetTextAlignment(HorizontalAlignment::Center);
        textBox1->SetRow(1);
        container->AddChild(textBox1);

        textBox2 = new TextBox();
        textBox2->SetName("MainTextBox2");
        textBox2->SetHintText("Enter your username here");
        textBox2->SetTextAlignment(HorizontalAlignment::Center);
        textBox2->SetRow(2);
        container->AddChild(textBox2);

        label1 = new Label();
        label1->SetName("MainLabel");
        label1->SetText("Welcome to the test program!");
        label1->SetRow(0);
        container->AddChild(label1);

        SetContent(container);
    }
}