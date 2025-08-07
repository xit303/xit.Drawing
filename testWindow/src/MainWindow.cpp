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
        button1 = nullptr;
    }

    MainWindow::~MainWindow()
    {
        if (container != nullptr)
        {
            delete container;
            container = nullptr;
        }
        if (button1 != nullptr)
        {
            delete button1;
            button1 = nullptr;
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
        container->SetRows("Auto,*,50, Auto");
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

        button1 = new Button();
        button1->SetName("MainButton");
        button1->SetText("Click Me!");
        button1->SetRow(3);
        button1->Click.Add([this](InputContent &sender, EventArgs &e) {
            static bool clicked = false;
            clicked = !clicked;
            button1->SetText(clicked ? "Clicked!" : "Click Me!");
            printf("[DEBUG] Button text changed to: %s\n", button1->GetText().c_str());
        });

        container->AddChild(button1);

        SetContent(container);
    }
}